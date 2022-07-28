#pragma once

class Player;
class Monster;

class Encounter
{
	Player* m_playerPt;
	Monster* m_monsterPt;
	void Round();
	void DisplayHealth();
	void PressAnyKeyToContinue();
public:
	Encounter(Player* playerPt, Monster* monsterPt);
	bool Run();
};
