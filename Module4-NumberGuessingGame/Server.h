#pragma once
#include <enet/enet.h>

class Server
{
	ENetHost* m_Server;
	int m_nextClientId;
	int m_numberOfPlayers;
	int m_numberToGuess;
	int m_currentGuessingPlayer;

	static const int requiredNumberOfPlayers = 2;
public:
	Server();
	~Server();
	void Run();
	int GetNextUserId();
private:
	void HandlePacket(ENetPacket* packet, ENetPeer* client);
	void ResetGame();
};
