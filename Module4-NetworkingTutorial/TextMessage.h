#pragma once
#include "NetworkMessage.h"
#include <string>

class TextMessage : public NetworkMessage
{
	std::string m_Content;
public:
	TextMessage(std::string content);
	~TextMessage();
	std::string GetContent() { return m_Content; }
};
