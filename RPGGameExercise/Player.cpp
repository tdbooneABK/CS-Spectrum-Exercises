#include <string>
#include "Character.h"
#include "Player.h"

Player::Player(std::string name, int weapon, int armorClass)
	: Character(name, weapon, armorClass)
{
}

int Player::GetDamage() {
	return 10;
}
