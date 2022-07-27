#include <string>
#include "Enemy.h"
#include "Weapon.h"
#include "Armor.h"

Enemy::Enemy()
	: Character(Enemy::GetRandomName(), (WeaponType)(rand() % 4), (ArmorClass)(rand() % 4))
{
}

const std::string Enemy::adjectives[] = { "Sweaty", "Hairy", "Smelly", "Snarling", "Drooling" };
const std::string Enemy::nouns[] = { "Ogre", "Wolf", "Goblin", "Murloc", "Donkey", "Siren" };
const int Enemy::adjectivesLength = 5;
const int Enemy::nounsLength = 6;

std::string Enemy::GetRandomName() {
	return Enemy::adjectives[rand() % Enemy::adjectivesLength] + " " + Enemy::nouns[rand() % Enemy::nounsLength];
}

int Enemy::GetDamage() {
	int damage = GetWeapon().GetWeaponDamage();
	return damage >= 1 ? damage - 1 : 0;
}
