#pragma once
#include "NetworkMessage.h"
class SubmitGuess : public NetworkMessage
{
	int m_Guess;
public:
	SubmitGuess(int guess);
	~SubmitGuess();
	int GetGuessValue() { return m_Guess; }
};
