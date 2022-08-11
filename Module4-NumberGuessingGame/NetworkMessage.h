#pragma once

enum MessageType {
	sendPlayerId,
	readyToPlay,
	submitGuess,
	broadcastGuess
};

class NetworkMessage {
	MessageType m_MessageType;
public:
	NetworkMessage(MessageType type);
	virtual ~NetworkMessage();
	MessageType GetType() { return m_MessageType; }
};
