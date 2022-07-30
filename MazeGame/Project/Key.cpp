#include <iostream>
#include <windows.h>

#include "Key.h"

void Key::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	std::cout << "+";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

std::string Key::GetName()
{
	std::string colorName = "";
	switch (m_color) {
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
	default :
		colorName = "Rusty";
	}
	return colorName + " Key";
}
