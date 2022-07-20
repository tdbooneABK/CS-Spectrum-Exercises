#include "Character.h"

Character::Character(float health, int x, int y)
	: m_Health(health),
	m_xPosition(x),
	m_yPosition(y),
	m_isAlive(true)
{

}

void Character::Move(int x, int y) {
	m_xPosition += x;
	m_yPosition += y;
}

void Character::TakeDamage(int damage) {
	m_Health -= damage;
	if (m_Health <= 0) {
		m_Health = 0;
		m_isAlive = false;
	}
}
