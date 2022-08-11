#include "BroadcastGuess.h"

BroadcastGuess::BroadcastGuess(int guess, int guessingPlayerId, int nextPlayerId)
	: NetworkMessage(MessageType::broadcastGuess)
	, m_Guess(guess)
	, m_GuessingPlayerId(guessingPlayerId)
	, m_NextPlayerId(nextPlayerId)
{}

BroadcastGuess::~BroadcastGuess()
{}
