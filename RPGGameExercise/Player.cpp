#include <string>
#include "Character.h"
#include "Player.h"
#include "Weapon.h"

Player::Player(std::string name, WeaponType weapon, ArmorClass armorClass)
	: Character(name, weapon, armorClass)
{
}

int Player::GetDamage() {
	return GetWeapon().GetWeaponDamage();
}
