#pragma once
#include "Player.h"

class Game
{
	Player* m_player;
public:
	Game();
	~Game();
	void Run();
};
