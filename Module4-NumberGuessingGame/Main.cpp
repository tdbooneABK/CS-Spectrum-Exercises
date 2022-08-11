#include <enet/enet.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Winmm.lib")

#include "Client.h"
#include "Server.h"

int main(int argc, char** argv)
{
    srand(time(0));
    std::cout << "Which service are you starting?" << std::endl
        << "1) Server" << std::endl
        << "2) Client" << std::endl;
    int input = 0;
    std::cin >> input;
    system("cls");
    switch (input) {
    case 1: {
        Server* server = new Server();
        server->Run();
        break;
    }
    case 2: {
        Client* client = new Client();
        client->Run();
        break;
    }
    default:
        std::cout << "What the hell are you doing?" << std::endl;
    }
}
