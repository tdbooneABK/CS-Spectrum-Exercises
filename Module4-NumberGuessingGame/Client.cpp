#include "Client.h"
#include <enet/enet.h>
#include <iostream>
#include <string>
#include <thread>
#include "SendPlayerId.h"
#include "ReadyToPlay.h"
#include "SubmitGuess.h"
#include "BroadcastGuess.h"

Client::Client() 
    : m_Client(nullptr)
    , m_ClientId(-1)
    , m_CurrentPlayer(0)
    , m_ShouldTerminate(false)
    , m_ReadyToGuess(false)
{
    if (enet_initialize() != 0)
    {
        std::cout << "An error occurred while initializing ENet." << std::endl;
        exit(EXIT_FAILURE);
    }
    atexit(enet_deinitialize);

    std::cout << "Creating a client..." << std::endl;
    m_Client = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);
    if (m_Client == NULL)
    {
        fprintf(stderr,
            "An error occurred while trying to create an ENet client host.\n");
        exit(EXIT_FAILURE);
    }
}

Client::~Client() {
    enet_host_destroy(m_Client);
}

void Client::Run() {
    ConnectToServer();
    std::thread PacketThread(&Client::ListenForPackets, this);
    std::thread GuessThread(&Client::ListenForGuessPrompt, this);
    PacketThread.join();
    GuessThread.join();
}

bool Client::ConnectToServer() {
    ENetAddress address;
    ENetEvent event;
    ENetPeer* peer;
    /* Connect to some.server.net:9000. */
    enet_address_set_host(&address, "localhost");
    address.port = 9000;
    /* Initiate the connection, allocating the two channels 0 and 1. */
    peer = enet_host_connect(m_Client, &address, 2, 0);
    if (peer == NULL)
    {
        fprintf(stderr,
            "No available peers for initiating an ENet connection.\n");
        exit(EXIT_FAILURE);
    }
    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service(m_Client, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        std::cout << "Connection to some.server.net:9000 succeeded." << std::endl;
        return true;
    }
    else
    {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset(peer);
        puts("Connection to some.server.net:9000 failed.");
    }
    return false;
}

void Client::ListenForPackets() {
    while (!m_ShouldTerminate) {
        ENetEvent event;
        while (enet_host_service(m_Client, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_RECEIVE: {
                NetworkMessage* message = (NetworkMessage*)event.packet->data;
                switch (message->GetType()) {
                case MessageType::sendPlayerId: {
                    SendPlayerId* playerIdMessage = (SendPlayerId*)event.packet->data;
                    m_ClientId = playerIdMessage->GetPlayerId();
                    std::cout << "You have joined the game. You are player " << m_ClientId << "." << std::endl;
                    break;
                }
                case MessageType::readyToPlay: {
                    ReadyToPlay* readyToPlayMessage = (ReadyToPlay*)event.packet->data;
                    m_CurrentPlayer = readyToPlayMessage->GetFirstPlayerId();
                    std::cout << "Time to start the game! Player " << m_CurrentPlayer << " goes first." << std::endl;
                    break;
                }
                case MessageType::broadcastGuess: {
                    BroadcastGuess* guessMessage = (BroadcastGuess*)event.packet->data;
                    if (guessMessage->GetNextPlayerId() == 0) {
                        if (guessMessage->GetGuessingPlayerId() == m_ClientId) {
                            std::cout << "You guessed correctly! You win!" << std::endl;
                        }
                        else {
                            std::cout << "Player " << guessMessage->GetGuessingPlayerId() << " correctly guessed "
                                << guessMessage->GetGuess() << "." << std::endl << "Better luck next time!" << std::endl;
                        }
                        m_ShouldTerminate = true;
                    }
                    else {
                        if (guessMessage->GetGuessingPlayerId() == m_ClientId) {
                            std::cout << guessMessage->GetGuess() << " is not the correct answer." << std::endl;
                        }
                        else {
                            std::cout << "Player " << guessMessage->GetGuessingPlayerId() << " incorrectly guessed "
                                << guessMessage->GetGuess() << "." << std::endl;
                        }
                        m_CurrentPlayer = guessMessage->GetNextPlayerId();
                    }
                    break;
                }
                default:
                    std::cout << "Unrecognized event! I'm not a server, leave me alone!" << std::endl;
                }
                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);
                if (m_CurrentPlayer == m_ClientId && !m_ShouldTerminate) {
                    m_ReadyToGuess = true;
                }
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "DISCONNECTED FROM SERVER" << std::endl;
            }
        }
    }
}

void Client::ListenForGuessPrompt() {
    while (!m_ShouldTerminate) {
        if (m_ReadyToGuess) {
            m_ReadyToGuess = false;
            GuessNumber();
        }
    }
}

void Client::GuessNumber() {
    int nextGuess = 0;
    std::cout << "Enter your guess: ";
    std::cin >> nextGuess;

    SubmitGuess* guessMessage = new SubmitGuess(nextGuess);
    ENetPacket* guessPacket = enet_packet_create(guessMessage,
        sizeof(SubmitGuess),
        ENET_PACKET_FLAG_RELIABLE);
    enet_host_broadcast(m_Client, 0, guessPacket);
    delete guessMessage;
}
