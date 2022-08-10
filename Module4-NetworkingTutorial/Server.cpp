#include "Server.h"
#include <enet/enet.h>
#include <iostream>
#include "SetUsernameMessage.h"
#include "TextMessage.h"

Server::Server()
    : m_Server(nullptr)
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
}

Server::~Server() {
    enet_host_destroy(m_Server);
}

void Server::Run() {
    while (true) {
        ENetEvent event;
        while (enet_host_service(m_Server, &event, 100) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT: {
                std::cout << "A new client connected from "
                    << event.peer->address.host << ":"
                    << event.peer->address.port << '.' << std::endl;
                /* Store any relevant client information here. */
                int* userId = new int(GetNextUserId());
                std::cout << "Assigning them id " << *userId << std::endl;
                event.peer->data = (void*)userId;
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE: {
                HandlePacket(event.packet);

                // Rebroadcast the message to everyone else.
                /*
                ENetPacket* packet = enet_packet_create(event.packet->data,
                    event.packet->dataLength,
                    ENET_PACKET_FLAG_RELIABLE);
                enet_host_broadcast(m_Server, 0, packet);
                enet_host_flush(m_Server);
                */

                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << event.peer->data << " disconnected." << std::endl;
                /* Reset the peer's client information. */
                event.peer->data = NULL;
            }
        }
    }
}

void Server::HandlePacket(ENetPacket* packet) {
    NetworkMessage* networkMessage = (NetworkMessage*)packet->data;
    switch (networkMessage->GetType()) {
    case MessageType::setUsername: {
        std::cout << "Received setUsername message" << std::endl;
        SetUsernameMessage* setUsernameMessage = (SetUsernameMessage*)packet->data;
        std::cout << "Username: " << setUsernameMessage->GetUsername() << std::endl;
        break;
    }
    case MessageType::textMessage: {
        std::cout << "Received text message" << std::endl;
        TextMessage* textMessage = (TextMessage*)packet->data;
        std::cout << "Message: " << textMessage->GetContent() << std::endl;
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
