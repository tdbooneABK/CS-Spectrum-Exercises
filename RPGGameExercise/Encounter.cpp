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
	std::cout << m_player.GetName() << " encounters a wild " << m_enemy.GetName() << " with " << m_enemy.GetHealth() << " health!" << std::endl;
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
	std::cout << std::endl;
	DisplayHealth();
	int playerDamage = m_player.GetDamage();
	std::cout << m_player.GetName() << " attacks for " << playerDamage << " damage!" << std::endl;
	m_enemy.DoDamage(playerDamage);
	if (m_enemy.GetHealth() > 0) {
		int enemyDamage = m_enemy.GetDamage();
		std::cout << m_enemy.GetName() << " attacks back for " << enemyDamage << " kdamage!" << std::endl;
		m_player.DoDamage(enemyDamage);
	}
	else {
		std::cout << m_enemy.GetName() << " has been defeated!" << std::endl;
	}
}

void Encounter::DisplayHealth() {
	std::cout << m_player.GetName() << ": " << m_player.GetHealth() << "   " << m_enemy.GetName() << ": " << m_enemy.GetHealth() << std::endl;
}
