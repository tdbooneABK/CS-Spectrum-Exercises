#include "Client.h"
#include <enet/enet.h>
#include <iostream>
#include <string>
#include <thread>
#include "SetUsernameMessage.h"
#include "TextMessage.h"

Client::Client() 
    : m_Client(nullptr)
    , m_Username("")
    , m_shouldTerminate(false)
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
    GetUsername();
    ConnectToServer();
    SendUsername();
    std::thread packetThread(&Client::ListenForPackets, this);
    std::thread inputThread(&Client::ListenForInputs, this);
    packetThread.join();
    inputThread.join();
}

void Client::GetUsername() {
    std::string inputString = "";
    std::cout << "Please enter your username:" << std::endl;
    std::cin >> inputString;
    m_Username = inputString;
}

void Client::SendUsername() {
    SetUsernameMessage setUsernameMessage = SetUsernameMessage(m_Username);
    ENetPacket* packet = enet_packet_create(&setUsernameMessage,
        sizeof(setUsernameMessage),
        ENET_PACKET_FLAG_RELIABLE);
    enet_host_broadcast(m_Client, 0, packet);
    enet_host_flush(m_Client);
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
        std::cout << "Connection to some.server.net:9000 succeeded.";
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
    while (!m_shouldTerminate) {
        ENetEvent event;
        while (enet_host_service(m_Client, &event, 100) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "A packet of length " << event.packet->dataLength
                    << " containing " << event.packet->data << " was received from "
                    << event.peer->data << " on channel " << event.channelID << '.' << std::endl;
                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);
                break;
            }
        }
    }
}

void Client::ListenForInputs() {
    while (!m_shouldTerminate) {
        std::string userInput = "";
        std::cout << m_Username << ": ";
        std::cin >> userInput;
        if (userInput == "!q") {
            m_shouldTerminate = true;
        }
        else {
            TextMessage textMessage = TextMessage(userInput);
            ENetPacket* packet = enet_packet_create(&textMessage,
                sizeof(textMessage),
                ENET_PACKET_FLAG_RELIABLE);
            enet_host_broadcast(m_Client, 0, packet);
            enet_host_flush(m_Client);
        }
    }
}
