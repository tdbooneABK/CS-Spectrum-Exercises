#pragma once
#include <string>
#include "Character.h"

class Enemy : public Character
{
	static std::string GetRandomName();
	static const std::string adjectives[];
	static const std::string nouns[];
	static const int adjectivesLength;
	static const int nounsLength;
public:
	Enemy();
	int GetDamage() override;
};
