#pragma once
#include <string>
#include "Armor.h"
#include "Weapon.h"

class Combatant
{
protected:
	std::string m_Name;
	int m_health;
	Weapon* m_pCurrentWeapon;
	Armor* m_pCurrentArmor;

public:
	Combatant(std::string name, WeaponType weaponType, ArmorClass armorClass);
	~Combatant();

	std::string GetName() { return m_Name; }

	int GetHealth() { return m_health; }
	bool ApplyDamage(int damageAmount, bool checkDodgeChance = false);

	Weapon* GetWeapon() { return m_pCurrentWeapon; }
	virtual int GetDamage();

	Armor* GetArmor() { return m_pCurrentArmor; }
};

