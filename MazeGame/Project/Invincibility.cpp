#include <iostream>
#include "Invincibility.h"

Invincibility::Invincibility(const int x, const int y)
	: PlacableActor(x, y)
{}

ActorType Invincibility::GetType() {
	return ActorType::Invincibility;
}

void Invincibility::Draw() {
	std::cout << "*";
}

