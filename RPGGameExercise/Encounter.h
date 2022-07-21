#pragma once
#include "Player.h"
#include "Enemy.h"

class Encounter
{
	Player m_player;
	Enemy m_enemy;
	void Round();
	void DisplayHealth();
public:
	Encounter(Player &player, Enemy &enemy);
	bool Run();
};
