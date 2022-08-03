#include <iostream>
#include <windows.h>

#include "Key.h"
#include "Player.h"
#include "AudioManager.h"

void Key::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	std::cout << "+";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

void Key::HandlePlayerCollision(Player* player) {
	if (player->PickupKey(this))
	{
		this->Remove();
		AudioManager::GetInstance()->PlayKeyPickupSound();
	}
	player->SetPosition(this->GetXPosition(), this->GetYPosition());
}
