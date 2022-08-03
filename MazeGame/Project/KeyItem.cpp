#include "KeyItem.h"

KeyItem::KeyItem(ActorColor keyColor)
	: m_KeyColor(keyColor)
{

}

KeyItem::~KeyItem()
{

}

std::string KeyItem::GetName()
{
	std::string colorName = "";
	switch (m_KeyColor) {
	case ActorColor::Blue:
	case ActorColor::SolidBlue:
		colorName = "Blue";
		break;
	case ActorColor::Green:
	case ActorColor::SolidGreen:
		colorName = "Green";
		break;
	case ActorColor::Red:
	case ActorColor::SolidRed:
		colorName = "Red";
		break;
	default:
		colorName = "Rusty";
	}
	return colorName + " Key";
}
