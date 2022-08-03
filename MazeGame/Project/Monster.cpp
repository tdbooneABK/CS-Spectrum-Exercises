#include <iostream>
#include <string>
#include "Monster.h"
#include "Player.h"
#include "Encounter.h"

Monster::Monster(int x, int y)
	: PlacableActor(x, y)
	, Combatant(Monster::GetRandomName(), (WeaponType)(rand() % 4), (ArmorClass)(rand() % 4))
{
}

Monster::~Monster()
{

}

ActorType Monster::GetType() {
	return ActorType::Monster;
}

void Monster::Draw() {
	std::cout << (char)142;
}

const std::string Monster::adjectives[] = { "Sweaty", "Hairy", "Smelly", "Snarling", "Drooling" };
const std::string Monster::nouns[] = { "Ogre", "Wolf", "Goblin", "Murloc", "Donkey", "Siren" };
const int Monster::adjectivesLength = 5;
const int Monster::nounsLength = 6;

std::string Monster::GetRandomName() {
	return Monster::adjectives[rand() % Monster::adjectivesLength] + " " + Monster::nouns[rand() % Monster::nounsLength];
}

int Monster::GetDamage() {
	int damage = GetWeapon()->GetWeaponDamage();
	return damage >= 1 ? damage - 1 : 0;
}

void Monster::HandlePlayerCollision(Player* player) {
	if (Encounter(player, this).Run()) {
		this->Remove();
		player->SetPosition(this->GetXPosition(), this->GetYPosition());
	}
}
