#include <string>
#include "Armor.h"

Armor::Armor(ArmorClass armorClass)
	: m_ArmorClass(armorClass)
{
}

std::string Armor::GetArmorName(ArmorClass armorClass) {
	switch (armorClass)
	{
	case Light:
		return "Light Armor";
	case Medium:
		return "Medium Armor";
	case Heavy:
		return "Heavy Armor";
	default:
		return "Regular Clothes";
	}
}

std::string Armor::GetArmorName() {
	return GetArmorName(m_ArmorClass);
}

int Armor::GetHealthBonus() {
	switch (m_ArmorClass) {
	case Light:
		return 10;
	case Medium:
		return 25;
	case Heavy:
		return 50;
	default:
		return 0;
	}
}

float Armor::GetDodgeChance() {
	switch (m_ArmorClass)
	{
	case Light:
		return 0.2f;
	case Medium:
		return 0.1f;
	case Heavy:
	default:
		return 0.0f;
	}
}
