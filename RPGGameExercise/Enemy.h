#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy();
	int GetDamage() override;
};
