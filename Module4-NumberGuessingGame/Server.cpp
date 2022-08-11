#include "Server.h"
#include <enet/enet.h>
#include <iostream>
#include "SendPlayerId.h"
#include "ReadyToPlay.h"
#include "SubmitGuess.h"
#include "BroadcastGuess.h"

Server::Server()
    : m_Server(nullptr)
    , m_nextClientId(0)
    , m_numberOfPlayers(0)
    , m_currentGuessingPlayer(0)
    , m_numberToGuess(0)
{
    if (enet_initialize() != 0)
    {
        std::cout << "An error occurred while initializing ENet." << std::endl;
        exit(EXIT_FAILURE);
    }
    atexit(enet_deinitialize);

    ENetAddress address;
    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    address.host = ENET_HOST_ANY;
    /* Bind the server to port 9000. */
    address.port = 9000;
    std::cout << "Creating a server." << std::endl;
    m_Server = enet_host_create(&address /* the address to bind the server host to */,
        32      /* allow up to 32 clients and/or outgoing connections */,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */);
    if (m_Server == NULL)
    {
        fprintf(stderr,
            "An error occurred while trying to create an ENet server host.\n");
        exit(EXIT_FAILURE);
    }
    ResetGame();
}

Server::~Server() {
    enet_host_destroy(m_Server);
}

void Server::Run() {
    while (true) {
        ENetEvent event;
        while (enet_host_service(m_Server, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT: {
                std::cout << "A new client connected from "
                    << event.peer->address.host << ":"
                    << event.peer->address.port << '.' << std::endl;
                
                int* userId = new int(GetNextUserId());
                std::cout << "Player " << *userId << " has joined the game." << std::endl;
                event.peer->data = (void*)userId;
                m_numberOfPlayers++;

                SendPlayerId* playerIdMessage = new SendPlayerId(*userId, Server::requiredNumberOfPlayers - m_numberOfPlayers);
                ENetPacket* playerIdPacket = enet_packet_create(playerIdMessage,
                    sizeof(SendPlayerId),
                    ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(event.peer, 0, playerIdPacket);
                delete playerIdMessage;
                playerIdMessage = nullptr;

                if (m_numberOfPlayers >= Server::requiredNumberOfPlayers) {
                    std::cout << "There are " << m_numberOfPlayers << " players and the game can now begin." << std::endl;
                    ReadyToPlay* readyToPlayMessage = new ReadyToPlay(m_currentGuessingPlayer);
                    ENetPacket* readyToPlayPacket = enet_packet_create(readyToPlayMessage,
                        sizeof(ReadyToPlay),
                        ENET_PACKET_FLAG_RELIABLE);
                    enet_host_broadcast(m_Server, 0, readyToPlayPacket);
                    delete readyToPlayMessage;
                    readyToPlayMessage = nullptr;
                }

                enet_host_flush(m_Server);
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE: {
                HandlePacket(event.packet, event.peer);
                enet_packet_destroy(event.packet);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "Player " << * ((int*)event.peer->data) << " disconnected." << std::endl;
                /* Reset the peer's client information. */
                event.peer->data = NULL;
            }
        }
    }
}

void Server::HandlePacket(ENetPacket* packet, ENetPeer* client) {
    NetworkMessage* networkMessage = (NetworkMessage*)packet->data;
    switch (networkMessage->GetType()) {
    case MessageType::submitGuess: {
        SubmitGuess* guessSubmissionMessage = (SubmitGuess*)packet->data;
        int* userIdPtr = (int*)client->data;
        std::cout << "User " << *userIdPtr << " guessed " << guessSubmissionMessage->GetGuessValue() << "." << std::endl;
        
        int nextPlayer = 0;
        if (guessSubmissionMessage->GetGuessValue() != m_numberToGuess) {
            nextPlayer = (m_currentGuessingPlayer % m_numberOfPlayers) + 1;
            m_currentGuessingPlayer = nextPlayer;
        }
        BroadcastGuess* broadcastGuessMessage = new BroadcastGuess(guessSubmissionMessage->GetGuessValue(), *userIdPtr, nextPlayer);
        ENetPacket* broadcastGuessPacket = enet_packet_create(broadcastGuessMessage,
            sizeof(BroadcastGuess),
            ENET_PACKET_FLAG_RELIABLE);
        enet_host_broadcast(m_Server, 0, broadcastGuessPacket);
        delete broadcastGuessMessage;

        if (nextPlayer == 0) {
            std::cout << "Game over!" << std::endl;
            // Disconnect all peers? Ask them to opt-in to playing again?
            ResetGame();
        }

        break;
    }
    default:
        std::cout << "Unknown message type. What did you do?" << std::endl;
    }
}

int Server::GetNextUserId() {
    int nextId = m_nextClientId;
    m_nextClientId++;
    return nextId;
}

void Server::ResetGame() {
    m_nextClientId = 1;
    m_currentGuessingPlayer = 1;
    m_numberOfPlayers = 0;
    m_numberToGuess = rand() % 100 + 1;
    std::cout << "The secret number is " << m_numberToGuess << ". Shh!" << std::endl;
}
