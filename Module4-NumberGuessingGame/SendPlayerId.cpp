#include "SendPlayerId.h"

SendPlayerId::SendPlayerId(int playerId, int remainingPlayers)
	: NetworkMessage(MessageType::sendPlayerId)
	, m_PlayerId(playerId)
	, m_RemainingPlayers(remainingPlayers)
{}

SendPlayerId::~SendPlayerId()
{}
