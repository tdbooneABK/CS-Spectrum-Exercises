#include "TextMessage.h"

TextMessage::TextMessage(std::string content)
	: NetworkMessage(MessageType::textMessage)
	, m_Content(content)
{}

TextMessage::~TextMessage()
{}