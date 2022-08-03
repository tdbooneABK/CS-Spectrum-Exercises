#include <iostream>
#include "Invincibility.h"
#include "Player.h"

Invincibility::Invincibility(const int x, const int y)
	: PlacableActor(x, y)
{}

ActorType Invincibility::GetType() {
	return ActorType::Invincibility;
}

void Invincibility::Draw() {
	std::cout << "*";
}

void Invincibility::HandlePlayerCollision(Player* player) {
	this->Remove();
	player->PickupInvincibililty();
	player->SetPosition(this->GetXPosition(), this->GetYPosition());
}
