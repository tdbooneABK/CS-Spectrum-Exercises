#pragma once
#include <enet/enet.h>
#include <string>
#include <atomic>

class Client
{
	ENetHost* m_Client;
	int m_ClientId;
	int m_CurrentPlayer;
	bool m_ShouldTerminate;
	std::atomic_bool m_ReadyToGuess;
	
public:
	Client();
	~Client();
	void Run();
private:
	bool ConnectToServer();
	void ListenForPackets();
	void ListenForGuessPrompt();
	void GuessNumber();
};
