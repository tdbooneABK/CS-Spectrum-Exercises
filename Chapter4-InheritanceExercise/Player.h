#pragma once
#include "Character.h"

class Player : public Character
{
	bool m_HasKey;

public:
	Player(int health, int x, int y);
	void Draw() override;
	void UseHealth(int healthAmount);
	void PickupKey();
};
