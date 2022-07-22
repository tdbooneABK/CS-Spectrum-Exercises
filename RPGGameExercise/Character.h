#pragma once
#include <string>
#include "Weapon.h"

class Character
{
	std::string m_Name;
	int m_Health;
	Weapon m_Weapon;
	int m_ArmorClass;

public:
	Character(std::string name, WeaponType weapon, int armorClass);
	std::string GetName();
	int GetHealth();
	Weapon GetWeapon();
	int GetArmorClass();
	virtual int GetDamage() = 0;
	void DoDamage(int damage);
};
