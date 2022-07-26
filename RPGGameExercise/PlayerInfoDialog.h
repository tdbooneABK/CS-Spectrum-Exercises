#pragma once
#include "Player.h"
#include <string>

class PlayerInfoDialog
{
	std::string GetPlayerName();
	int GetWeapon();
	int GetArmorClass();
	void PrintPlayerInfo(Player player);
public:
	Player* GetPlayerInfo();
};
