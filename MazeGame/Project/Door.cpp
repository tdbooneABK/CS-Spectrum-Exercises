#include <iostream>
#include <windows.h>
#include "Door.h"
#include "Player.h"
#include "AudioManager.h"

Door::Door(int x, int y, ActorColor color, ActorColor closedColor)
	: PlacableActor(x, y, color)
	, m_isOpen(false)
	, m_closedColor(closedColor)
{

}

void Door::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_isOpen)
	{
		SetConsoleTextAttribute(console, (int)m_color);
	}
	else
	{
		SetConsoleTextAttribute(console, (int)m_closedColor);
	}
	std::cout << "|";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

void Door::HandlePlayerCollision(Player* player) {
	if (!this->IsOpen())
	{
		if (player->HasKey(this->GetColor()))
		{
			this->Open();
			this->Remove();
			player->UseKey(this->GetColor());
			player->SetPosition(this->GetXPosition(), this->GetYPosition());
			AudioManager::GetInstance()->PlayDoorOpenSound();
		}
		else
		{
			AudioManager::GetInstance()->PlayDoorClosedSound();
		}
	}
	else
	{
		player->SetPosition(this->GetXPosition(), this->GetYPosition());
	}
}
