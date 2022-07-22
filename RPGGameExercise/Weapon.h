#pragma once
#include <string>

enum WeaponType {
	Sword=1,
	Axe,
	Bow
};

class Weapon
{
	WeaponType m_Type;
public:
	static const int maxWeaponType = 3;
	Weapon(WeaponType weaponType);
	static std::string GetWeaponName(WeaponType type);
	std::string GetWeaponName();
	int GetWeaponDamage();
};
