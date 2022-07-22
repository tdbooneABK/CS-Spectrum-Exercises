#include "Weapon.h"

Weapon::Weapon(WeaponType weaponType)
	: m_Type(weaponType)
{
}

std::string Weapon::GetWeaponName(WeaponType type) {
	switch (type) {
		case Sword:
			return "Sword";
		case Axe:
			return "Axe";
		case Bow:
			return "Bow";
		default:
			return "Bare Fist";
	}
}

std::string Weapon::GetWeaponName() {
	return Weapon::GetWeaponName(m_Type);
}

int Weapon::GetWeaponDamage() {
	switch (m_Type) {
		case Sword:
			return 5 + rand() % 4;
		case Axe:
			return 3 + rand() % 8;
		case Bow:
			return ((rand() % 100) > 60) * (10 + rand() % 4);
		default:
			return 1 + rand() % 4;
	}
}
