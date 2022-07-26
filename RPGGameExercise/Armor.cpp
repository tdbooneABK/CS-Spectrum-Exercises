#include <string>
#include "Armor.h"

Armor::Armor(ArmorClass armorClass)
	: m_ArmorClass(armorClass)
{
}

std::string Armor::GetArmorName(ArmorClass armorClass) {
	switch (armorClass)
	{
	case ArmorClass::Light:
		return "Light Armor";
	case ArmorClass::Medium:
		return "Medium Armor";
	case ArmorClass::Heavy:
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
	case ArmorClass::Light:
		return 10;
	case ArmorClass::Medium:
		return 25;
	case ArmorClass::Heavy:
		return 50;
	default:
		return 0;
	}
}

float Armor::GetDodgeChance() {
	switch (m_ArmorClass)
	{
	case ArmorClass::Light:
		return 0.2f;
	case ArmorClass::Medium:
		return 0.1f;
	case ArmorClass::Heavy:
	default:
		return 0.0f;
	}
}
