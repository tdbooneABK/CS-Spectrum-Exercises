#include "SetUsernameMessage.h"

SetUsernameMessage::SetUsernameMessage(std::string username)
	: NetworkMessage(MessageType::setUsername)
	, m_Username(username)
{}

SetUsernameMessage::~SetUsernameMessage()
{}
