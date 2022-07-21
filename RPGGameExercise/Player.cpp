#include "Player.h"
#include <string>

Player::Player(std::string name, int weapon, int armorClass)
	: m_Name(name)
	, m_Health(100)
	, m_Weapon(weapon)
	, m_ArmorClass(armorClass)
{

}

std::string Player::GetName() {
	return m_Name;
};

int Player::GetHealth() {
	return m_Health;
};

int Player::GetWeapon() {
	return m_Weapon;
};

int Player::GetArmorClass() {
	return m_ArmorClass;
};
