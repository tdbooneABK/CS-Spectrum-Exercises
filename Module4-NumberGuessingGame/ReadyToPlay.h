#pragma once
#include "NetworkMessage.h"

class ReadyToPlay : public NetworkMessage
{
	int m_FirstPlayerId;
public:
	ReadyToPlay(int firstPlayerId);
	~ReadyToPlay();
	int GetFirstPlayerId() { return m_FirstPlayerId; }
};
