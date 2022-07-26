#include <string>
#include "Character.h"
#include "Weapon.h"
#include "Armor.h"

Character::Character(std::string name, WeaponType weaponType, ArmorClass armorClass)
	: m_Name(name),
	m_Health(100),
	m_Weapon(Weapon(weaponType)),
	m_Armor(Armor(armorClass))
{
	m_Health += m_Armor.GetHealthBonus();
}

std::string Character::GetName() {
	return m_Name;
};

int Character::GetHealth() {
	return m_Health;
};

Weapon Character::GetWeapon() {
	return m_Weapon;
};

Armor Character::GetArmor() {
	return m_Armor;
};

// If player dodges attack, return false. Otherwise return true
bool Character::DoDamage(int damage) {
	if ((rand() % 100 + 1) < m_Armor.GetDodgeChance() * 100) {
		return false;
	}
	else {
		m_Health -= damage;
		if (m_Health < 0) {
			m_Health = 0;
		}
		return true;
	}
}

void Character::AddHealth(int healthAmount) {
	// If character has more than max health, then this could actually decrease their health, and we don't want that.
	if (m_Health < Character::maxHealth) {
		m_Health += healthAmount;
		if (m_Health > Character::maxHealth) {
			m_Health = Character::maxHealth;
		}
	}
}
