#include "Combatant.h"

Combatant::Combatant(std::string name, WeaponType weaponType, ArmorClass armorClass)
	: m_Name(name)
	, m_pCurrentWeapon(new Weapon(weaponType))
	, m_pCurrentArmor(new Armor(armorClass))
	, m_health(100)
{
	m_health += m_pCurrentArmor->GetHealthBonus();
}

Combatant::~Combatant() {
	if (m_pCurrentWeapon != nullptr) {
		delete m_pCurrentWeapon;
		m_pCurrentWeapon = nullptr;
	}
	if (m_pCurrentArmor != nullptr) {
		delete m_pCurrentArmor;
		m_pCurrentArmor = nullptr;
	}
}

int Combatant::GetDamage() {
	return m_pCurrentWeapon->GetWeaponDamage();
}

bool Combatant::ApplyDamage(int damageAmount, bool checkDodgeChance) {
	if (checkDodgeChance && (m_pCurrentArmor->GetDodgeChance() * 100 > rand() * 100)) {
		return false;
	}
	else {
		m_health -= damageAmount;
		if (m_health < 0) {
			m_health = 0;
		}
		return true;
	}
}
