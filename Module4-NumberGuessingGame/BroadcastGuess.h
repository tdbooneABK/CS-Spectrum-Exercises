#pragma once
#include "NetworkMessage.h"
class BroadcastGuess : public NetworkMessage
{
	int m_Guess;
	int m_GuessingPlayerId;
	int m_NextPlayerId; // Returns 0 when this guess was correct and the game is over

public:
	BroadcastGuess(int guess, int guessingPlayerId, int nextPlayerId);
	~BroadcastGuess();
	int GetGuess() { return m_Guess; }
	int GetGuessingPlayerId() { return m_GuessingPlayerId; }
	int GetNextPlayerId() { return m_NextPlayerId; }
};
