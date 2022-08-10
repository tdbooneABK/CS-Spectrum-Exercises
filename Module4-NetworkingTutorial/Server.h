#pragma once
#include <enet/enet.h>

class Server
{
	ENetHost* m_Server;
	int m_nextClientId;
public:
	Server();
	~Server();
	void Run();
	int GetNextUserId();
private:
	void HandlePacket(ENetPacket* packet);
};
