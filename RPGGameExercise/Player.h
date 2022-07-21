#pragma once
#include <string>

class Player
{
	std::string m_Name;
	int m_Health;
	int m_Weapon;
	int m_ArmorClass;

public:
	Player(std::string name, int weapon, int armorClass);
	std::string GetName();
	int GetHealth();
	int GetWeapon();
	int GetArmorClass();
};
