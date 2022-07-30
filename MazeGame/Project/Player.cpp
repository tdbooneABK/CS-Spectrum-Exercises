#include <iostream>
#include "assert.h"

#include "Player.h"
#include "Key.h"
#include "AudioManager.h"
#include "Armor.h"
#include "Weapon.h"

using namespace std;

Player::Player(std::string name, WeaponType weaponType, ArmorClass armorClass)
	: PlacableActor(0, 0)
	, Combatant(name, weaponType, armorClass)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_invincibilityCountdown(0)
	, m_Inventory(new Inventory())
{
}

Player::~Player() {
	delete m_Inventory;
	m_Inventory = nullptr;
}

bool Player::HasKey(ActorColor color)
{
	for (int i = 0; i < Inventory::k_inventorySize; i++) {
		InventoryItem* item = m_Inventory->GetInventoryItem(i);
		if (item && item->GetType() == ActorType::Key) {
			Key* key = dynamic_cast<Key*>(item);
			assert(key);
			if (key->GetColor() == color) {
				return true;
			}
		}
	}
	return false;
}

bool Player::PickupKey(Key* key)
{
	return m_Inventory->AddItem(key);
}

bool Player::UseKey(ActorColor color)
{
	for (int i = 0; i < Inventory::k_inventorySize; i++) {
		InventoryItem* item = m_Inventory->GetInventoryItem(i);
		if (item && item->GetType() == ActorType::Key) {
			Key* key = dynamic_cast<Key*>(item);
			assert(key);
			if (key->GetColor() == color) {
				m_Inventory->DropItem(i);
				delete key;
				return true;
			}
		}
	}
	return false;
}

bool Player::IsInvincible()
{
	return m_invincibilityCountdown > 0;
}

void Player::PickupInvincibililty()
{
	m_invincibilityCountdown = 25;
}

bool Player::IsAlive()
{
	return m_health > 0;
}

void Player::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_invincibilityCountdown > 10) {
		SetConsoleTextAttribute(console, (int)ActorColor::Green);
	}
	// When less than 10 frames are left, alternate between red and green
	else if (m_invincibilityCountdown > 0) {
		if (m_invincibilityCountdown % 2 == 0) {
			SetConsoleTextAttribute(console, (int)ActorColor::Red);
		}
		else {
			SetConsoleTextAttribute(console, (int)ActorColor::Green);
		}
	}

	cout << "@";

	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

void Player::Update()
{
	if (m_invincibilityCountdown > 0) {
		m_invincibilityCountdown -= 1;
	}
}
