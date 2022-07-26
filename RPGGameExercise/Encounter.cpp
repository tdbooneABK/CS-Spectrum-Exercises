#include <iostream>
#include "Encounter.h"

Encounter::Encounter(Player* playerPt, Enemy* enemyPt)
	: m_playerPt(playerPt),
	m_enemyPt(enemyPt)
{
}

/*
	If player succeeds return true; if player is defeated return false
*/
bool Encounter::Run() {
	std::cout << m_playerPt->GetName() << " encounters a wild " << m_enemyPt->GetName()
		<< " wielding a " << m_enemyPt->GetWeapon().GetWeaponName() << " and wearing "
		<< m_enemyPt->GetArmor().GetArmorName() << "!" << std::endl;
	DisplayHealth();
	PressAnyKeyToContinue();
	do {
		Round();
	} while (m_playerPt->GetHealth() > 0 && m_enemyPt->GetHealth() > 0);
	if (m_playerPt->GetHealth() <= 0) {
		std::cout << m_playerPt->GetName() << " has died!" << std::endl;
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
		if (m_enemyPt->DoDamage(playerDamage)) {
			std::cout << m_playerPt->GetName() << " attacks for " << playerDamage << " damage!" << std::endl;
		}
		else {
			std::cout << m_playerPt->GetName() << " attacks, but " << m_enemyPt->GetName() << " dodges the attack!" << std::endl;
		}		
	}
	else {
		std::cout << m_playerPt->GetName() << " tries to attack, but misses!" << std::endl;
	}
	if (m_enemyPt->GetHealth() > 0) {
		int enemyDamage = m_enemyPt->GetDamage();
		if (enemyDamage > 0) {
			if (m_playerPt->DoDamage(enemyDamage)) {
				std::cout << m_enemyPt->GetName() << " attacks back for " << enemyDamage << " damage!" << std::endl;
			}
			else {
				std::cout << m_enemyPt->GetName() << " attacks, but " << m_playerPt->GetName() << " dodges the attack!" << std::endl;
			}
		}
		else {
			std::cout << m_enemyPt->GetName() << " tries attacking back, but misses embarrassingly!" << std::endl;
		}
	}
	else {
		std::cout << m_enemyPt->GetName() << " has been defeated!" << std::endl;
	}
	DisplayHealth();
	PressAnyKeyToContinue();
}

void Encounter::DisplayHealth() {
	std::cout << m_playerPt->GetName() << ": " << m_playerPt->GetHealth() << "   " << m_enemyPt->GetName() << ": " << m_enemyPt->GetHealth() << std::endl;
}

void Encounter::PressAnyKeyToContinue() {
	std::cout << std::endl << "Press enter to continue..." << std::endl;
	std::cin.get();
}
