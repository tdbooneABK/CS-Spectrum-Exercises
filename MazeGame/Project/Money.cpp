#include <iostream>
#include "Money.h"
#include "AudioManager.h"
#include "Player.h"

Money::Money(int x, int y, int worth)
	: PlacableActor(x, y)
	, m_worth(worth)
{

}

void Money::Draw()
{
	std::cout << "$";
}

void Money::HandlePlayerCollision(Player* player) {
	AudioManager::GetInstance()->PlayMoneySound();
	this->Remove();
	player->AddMoney(this->GetWorth());
	player->SetPosition(this->GetXPosition(), this->GetYPosition());
}
