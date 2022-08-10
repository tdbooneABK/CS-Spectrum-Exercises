#pragma once
#include "NetworkMessage.h"
#include <string>

class SetUsernameMessage : public NetworkMessage
{
	std::string m_Username;
public:
	SetUsernameMessage(std::string username);
	~SetUsernameMessage();
	std::string GetUsername() { return m_Username; }
};
