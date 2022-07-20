#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int health, int x, int y, float strength)
	: Character(health, x, y),
	m_Strength(strength)
{

}

void Enemy::Draw() {
	std::cout << "*";
}
