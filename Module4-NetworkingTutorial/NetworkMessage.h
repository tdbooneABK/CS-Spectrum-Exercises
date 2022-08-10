#pragma once

enum MessageType {
	setUsername,
	textMessage
};

class NetworkMessage {
	MessageType m_MessageType;
public:
	NetworkMessage(MessageType type);
	virtual ~NetworkMessage();
	MessageType GetType() { return m_MessageType; }
};
