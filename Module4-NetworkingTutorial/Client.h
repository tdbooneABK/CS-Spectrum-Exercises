#pragma once
#include <enet/enet.h>
#include <string>

class Client
{
	ENetHost* m_Client;
	std::string m_Username;
	bool m_shouldTerminate;
	
public:
	Client();
	~Client();
	void Run();
private:
	void GetUsername();
	bool ConnectToServer();
	void SendUsername();
	void ListenForPackets();
	void ListenForInputs();
};
