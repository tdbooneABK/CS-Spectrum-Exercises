#pragma once
#include <string>
#include "Character.h"

class Player : public Character
{
public:
	Player(std::string name, int weapon, int armorClass);
	int GetDamage() override;
};
