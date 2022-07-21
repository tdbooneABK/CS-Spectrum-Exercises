#include <string>
#include "Character.h"

Character::Character(std::string name, int weapon, int armorClass)
	: m_Name(name),
	m_Health(100),
	m_Weapon(weapon),
	m_ArmorClass(armorClass)
{
}

std::string Character::GetName() {
	return m_Name;
};

int Character::GetHealth() {
	return m_Health;
};

int Character::GetWeapon() {
	return m_Weapon;
};

int Character::GetArmorClass() {
	return m_ArmorClass;
};

void Character::DoDamage(int damage) {
	m_Health -= damage;
	if (m_Health < 0) {
		m_Health = 0;
	}
}
