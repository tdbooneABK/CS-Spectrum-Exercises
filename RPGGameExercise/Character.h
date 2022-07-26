#pragma once
#include <string>
#include "Weapon.h"
#include "Armor.h"

class Character
{
	static const int maxHealth = 100;
	
	std::string m_Name;
	int m_Health;
	Weapon m_Weapon;
	Armor m_Armor;

public:
	Character(std::string name, WeaponType weapon, ArmorClass armorClass);
	std::string GetName();
	int GetHealth();
	Weapon GetWeapon();
	Armor GetArmor();
	virtual int GetDamage() = 0;
	bool DoDamage(int damage);
	void AddHealth(int healthAmount);
};
