#include <iostream>
#include "Encounter.h"
#include "Player.h"
#include "Monster.h"

Encounter::Encounter(Player* playerPt, Monster* monsterPt)
	: m_playerPt(playerPt),
	m_monsterPt(monsterPt)
{
}

/*
	If player succeeds return true; if player is defeated return false
*/
bool Encounter::Run() {
	system("cls");
	std::cout << m_playerPt->GetName() << " encounters a wild " << m_monsterPt->GetName()
		<< " wielding a " << m_monsterPt->GetWeapon()->GetWeaponName() << " and wearing "
		<< m_monsterPt->GetArmor()->GetArmorName() << "!" << std::endl;
	DisplayHealth();
	PressAnyKeyToContinue();
	do {
		Round();
	} while (m_playerPt->GetHealth() > 0 && m_monsterPt->GetHealth() > 0);
	if (m_playerPt->GetHealth() <= 0) {
		std::cout << m_playerPt->GetName() << " has died!" << std::endl;
		PressAnyKeyToContinue();
		return false;
	}
	else {
		return true;
	}
}

void Encounter::Round() {
	system("cls");
	int playerDamage = m_playerPt->GetDamage();
	if (playerDamage > 0) {
		if (m_monsterPt->ApplyDamage(playerDamage, true)) {
			std::cout << m_playerPt->GetName() << " attacks for " << playerDamage << " damage!" << std::endl;
		}
		else {
			std::cout << m_playerPt->GetName() << " attacks, but " << m_monsterPt->GetName() << " dodges the attack!" << std::endl;
		}		
	}
	else {
		std::cout << m_playerPt->GetName() << " tries to attack, but misses!" << std::endl;
	}
	if (m_monsterPt->GetHealth() > 0) {
		int enemyDamage = m_monsterPt->GetDamage();
		if (enemyDamage > 0) {
			if (m_playerPt->ApplyDamage(enemyDamage, true)) {
				std::cout << m_monsterPt->GetName() << " attacks back for " << enemyDamage << " damage!" << std::endl;
			}
			else {
				std::cout << m_monsterPt->GetName() << " attacks, but " << m_playerPt->GetName() << " dodges the attack!" << std::endl;
			}
		}
		else {
			std::cout << m_monsterPt->GetName() << " tries attacking back, but misses embarrassingly!" << std::endl;
		}
	}
	else {
		std::cout << m_monsterPt->GetName() << " has been defeated!" << std::endl;
	}
	DisplayHealth();
	PressAnyKeyToContinue();
}

void Encounter::DisplayHealth() {
	std::cout << m_playerPt->GetName() << ": " << m_playerPt->GetHealth() << "   " << m_monsterPt->GetName() << ": " << m_monsterPt->GetHealth() << std::endl;
}

void Encounter::PressAnyKeyToContinue() {
	std::cout << std::endl << "Press enter to continue..." << std::endl;
	std::cin.get();
}
