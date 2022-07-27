#pragma once
#include <string>

enum class ArmorClass {
	Light = 1,
	Medium,
	Heavy
};

class Armor
{
	ArmorClass m_ArmorClass;
public:
	static const int maxArmorClass = 3;
	Armor(ArmorClass armorClass);
	~Armor();
	static std::string GetArmorName(ArmorClass armorClass);
	std::string GetArmorName();
	int GetHealthBonus();
	float GetDodgeChance();
};
