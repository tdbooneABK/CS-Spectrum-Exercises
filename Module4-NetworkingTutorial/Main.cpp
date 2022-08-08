#include <enet/enet.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Winmm.lib")

int main(int argc, char** argv)
{
    if (enet_initialize() != 0)
    {
        std::cout << "An error occurred while initializing ENet." << std::endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);
}
