#include "ReadyToPlay.h"

ReadyToPlay::ReadyToPlay(int firstPlayerId)
	: NetworkMessage(MessageType::readyToPlay)
	, m_FirstPlayerId(firstPlayerId)
{}

ReadyToPlay::~ReadyToPlay()
{}
