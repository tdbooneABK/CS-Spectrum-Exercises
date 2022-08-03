#pragma once
#include <string>
#include "PlacableActor.h"
#include "Combatant.h"

class Monster : public PlacableActor, public Combatant
{
	static std::string GetRandomName();
	static const std::string adjectives[];
	static const std::string nouns[];
	static const int adjectivesLength;
	static const int nounsLength;
public:
	Monster(int x, int y);
	~Monster();
	int GetDamage() override;
	ActorType GetType() override;
	void Draw() override;
	void HandlePlayerCollision(Player* player) override;
};
