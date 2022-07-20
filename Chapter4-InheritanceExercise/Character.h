#pragma once

class Character {
protected:
	float m_Health;
	int m_xPosition;
	int m_yPosition;
	bool m_isAlive;

public:
	Character(float health, int x, int y);
	void Move(int x, int y);
	void TakeDamage(int damage);
	virtual void Draw() = 0;
};
