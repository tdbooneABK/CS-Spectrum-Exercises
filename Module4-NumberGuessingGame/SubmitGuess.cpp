#include "SubmitGuess.h"

SubmitGuess::SubmitGuess(int guess)
	: NetworkMessage(MessageType::submitGuess)
	, m_Guess(guess)
{}

SubmitGuess::~SubmitGuess()
{}
