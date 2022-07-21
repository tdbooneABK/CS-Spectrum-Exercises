#include <string>
#include "Enemy.h"

Enemy::Enemy()
	: Character("Enemy", rand() % 4, rand() % 4)
{
}

int Enemy::GetDamage() {
	return 7;
}
