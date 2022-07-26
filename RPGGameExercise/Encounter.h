#pragma once
#include "Player.h"
#include "Enemy.h"

class Encounter
{
	Player* m_playerPt;
	Enemy* m_enemyPt;
	void Round();
	void DisplayHealth();
	void PressAnyKeyToContinue();
public:
	Encounter(Player* playerPt, Enemy* enemyPt);
	bool Run();
};
