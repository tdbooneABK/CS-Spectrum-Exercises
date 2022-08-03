#include <iostream>
#include "Goal.h"
#include "Player.h"

Goal::Goal(int x, int y)
	: PlacableActor(x, y)
{
	
}

void Goal::Draw()
{
	std::cout << "X";
}

void Goal::HandlePlayerCollision(Player* player) {
	this->Remove();
	player->SetPosition(this->GetXPosition(), this->GetYPosition());
	player->ReachLevelExit();
}
