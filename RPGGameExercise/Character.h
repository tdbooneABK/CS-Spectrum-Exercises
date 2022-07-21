#pragma once
#include <string>

class Character
{
	std::string m_Name;
	int m_Health;
	int m_Weapon;
	int m_ArmorClass;

public:
	Character(std::string name, int weapon, int armorClass);
	std::string GetName();
	int GetHealth();
	int GetWeapon();
	int GetArmorClass();
	virtual int GetDamage() = 0;
	void DoDamage(int damage);
};
