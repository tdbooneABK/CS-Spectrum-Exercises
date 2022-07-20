#pragma once
#include "Character.h"
class Enemy : public Character
{
	float m_Strength;

public:
	Enemy(int health, int x, int y, float strength);
	void Draw() override;
};
