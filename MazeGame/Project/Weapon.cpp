#include <iostream>
#include "Weapon.h"

Weapon::Weapon(WeaponType weaponType)
	: m_Type(weaponType)
{
}

Weapon::~Weapon()
{
}

std::string Weapon::GetWeaponName(WeaponType type) {
	switch (type) {
		case WeaponType::Sword:
			return "Sword";
		case WeaponType::Axe:
			return "Axe";
		case WeaponType::Bow:
			return "Bow";
		default:
			return "Bare Fist";
	}
}

std::string Weapon::GetWeaponName() {
	return Weapon::GetWeaponName(m_Type);
}

std::string Weapon::GetName() {
	return GetWeaponName();
}

int Weapon::GetWeaponDamage() {
	switch (m_Type) {
		case WeaponType::Sword:
			// 5 - 8 damage
			return 5 + rand() % 4;
		case WeaponType::Axe:
			// 3 - 10 damage
			return 3 + rand() % 8;
		case WeaponType::Bow:
			// 60% hit chance for 10 - 13 damage
			return ((rand() % 100) > 60) * (10 + rand() % 4);
		default:
			return 1 + rand() % 4;
	}
}

void Weapon::Draw() {
	switch (m_Type) {
	case WeaponType::Sword:
		std::cout << (char)197;
		break;
	case WeaponType::Axe:
		std::cout << (char)203;
		break;
	case WeaponType::Bow:
		std::cout << 'D';
		break;
	default:
		std::cout << ' ';
	}
}
