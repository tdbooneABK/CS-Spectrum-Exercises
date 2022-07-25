#include <iostream>
#include "Encounter.h"

Encounter::Encounter(Player& player, Enemy& enemy)
	: m_player(player),
	m_enemy(enemy)
{
}

/*
	If player succeeds return true; if player is defeated return false
*/
bool Encounter::Run() {
	std::cout << m_player.GetName() << " encounters a wild " << m_enemy.GetName()
		<< " wielding a " << m_enemy.GetWeapon().GetWeaponName() << " and wearing "
		<< m_enemy.GetArmor().GetArmorName() << "!" << std::endl;
	DisplayHealth();
	PressAnyKeyToContinue();
	do {
		Round();
	} while (m_player.GetHealth() > 0 && m_enemy.GetHealth() > 0);
	if (m_player.GetHealth() <= 0) {
		return false;
	}
	else {
		return true;
	}
}

void Encounter::Round() {
	system("cls");
	DisplayHealth(); // Show "before" health for debugging purposes
	int playerDamage = m_player.GetDamage();
	if (playerDamage > 0) {
		if (m_enemy.DoDamage(playerDamage)) {
			std::cout << m_player.GetName() << " attacks for " << playerDamage << " damage!" << std::endl;
		}
		else {
			std::cout << m_player.GetName() << " attacks, but " << m_enemy.GetName() << " dodges the attack!" << std::endl;
		}		
	}
	else {
		std::cout << m_player.GetName() << " tries to attack, but misses!" << std::endl;
	}
	if (m_enemy.GetHealth() > 0) {
		int enemyDamage = m_enemy.GetDamage();
		if (enemyDamage > 0) {
			if (m_player.DoDamage(enemyDamage)) {
				std::cout << m_enemy.GetName() << " attacks back for " << enemyDamage << " damage!" << std::endl;
			}
			else {
				std::cout << m_enemy.GetName() << " attacks, but " << m_player.GetName() << " dodges the attack!" << std::endl;
			}
		}
		else {
			std::cout << m_enemy.GetName() << " tries attacking back, but misses embarrassingly!" << std::endl;
		}
	}
	else {
		std::cout << m_enemy.GetName() << " has been defeated!" << std::endl;
	}
	DisplayHealth();
	PressAnyKeyToContinue();
}

void Encounter::DisplayHealth() {
	std::cout << m_player.GetName() << ": " << m_player.GetHealth() << "   " << m_enemy.GetName() << ": " << m_enemy.GetHealth() << std::endl;
}

void Encounter::PressAnyKeyToContinue() {
	std::cout << std::endl << "Press enter to continue..." << std::endl;
	std::cin.get();
}
