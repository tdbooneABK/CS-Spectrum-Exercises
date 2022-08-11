#pragma once
#include "NetworkMessage.h"

class SendPlayerId : public NetworkMessage
{
	int m_PlayerId;
	int m_RemainingPlayers;
public:
	SendPlayerId(int playerId, int remainingPlayers);
	~SendPlayerId();
	int GetPlayerId() { return m_PlayerId; }
};
