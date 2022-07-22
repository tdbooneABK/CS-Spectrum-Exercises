#include <string>
#include "Enemy.h"
#include "Weapon.h"

Enemy::Enemy()
	: Character("Enemy", (WeaponType)(rand() % 4), rand() % 4)
{
}

int Enemy::GetDamage() {
	int damage = GetWeapon().GetWeaponDamage();
	return damage >= 1 ? damage - 1 : 0;
}
