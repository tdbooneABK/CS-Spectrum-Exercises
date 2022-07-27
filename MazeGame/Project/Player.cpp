#include <iostream>

#include "Player.h"
#include "Key.h"
#include "AudioManager.h"
#include "Armor.h"
#include "Weapon.h"

using namespace std;

constexpr int kStartingNumberOfLives = 3;

Player::Player(std::string name, WeaponType weaponType, ArmorClass armorClass)
	: PlacableActor(0, 0)
	, m_Name(name)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_health(100)
	, m_invincibilityCountdown(0)
	, m_pCurrentWeapon(new Weapon(weaponType))
	, m_pCurrentArmor(new Armor(armorClass))
{
	m_health += m_pCurrentArmor->GetHealthBonus();
}

Player::~Player() {
	if (m_pCurrentWeapon != nullptr) {
		delete m_pCurrentWeapon;
		m_pCurrentWeapon = nullptr;
	}
	if (m_pCurrentArmor != nullptr) {
		delete m_pCurrentArmor;
		m_pCurrentArmor = nullptr;
	}
}

bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}

bool Player::IsInvincible()
{
	return m_invincibilityCountdown > 0;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = key;
}

void Player::PickupInvincibililty()
{
	m_invincibilityCountdown = 25;
}

bool Player::IsAlive()
{
	return m_health > 0;
}

void Player::ApplyDamage(int damageAmount) {
	m_health -= damageAmount;
	if (m_health < 0) {
		m_health = 0;
	}
}

void Player::UseKey()
{
	if (m_pCurrentKey)
	{
		m_pCurrentKey->Remove();
		m_pCurrentKey = nullptr;
	}
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		AudioManager::GetInstance()->PlayKeyDropSound();
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
	}
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
