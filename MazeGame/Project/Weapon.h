#pragma once
#include <string>
#include "InventoryItem.h"

enum class WeaponType {
	Sword=1,
	Axe,
	Bow
};

class Weapon : public InventoryItem
{
	WeaponType m_Type;
public:
	static const int maxWeaponType = 3;
	Weapon(WeaponType weaponType);
	~Weapon();
	static std::string GetWeaponName(WeaponType type);
	std::string GetWeaponName();
	int GetWeaponDamage();
	void Draw() override;
	std::string GetName() override;
};
