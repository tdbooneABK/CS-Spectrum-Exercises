#pragma once
#include <string>
#include "Character.h"
#include "Weapon.h"

class Player : public Character
{
public:
	Player(std::string name, WeaponType weapon, int armorClass);
	int GetDamage() override;
};
