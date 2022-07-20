#include "Player.h"
#include <iostream>

Player::Player(int health, int x, int y)
	: Character(health, x, y),
	m_HasKey(false)
{

}

void Player::Draw() {
	std::cout << "@";
}

void Player::UseHealth(int healthAmount) {
	m_Health += healthAmount;
	if (!m_isAlive) {
		m_isAlive = true;
	}
}

void Player::PickupKey() {
	m_HasKey = true;
}
