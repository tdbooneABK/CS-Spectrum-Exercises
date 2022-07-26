#include <iostream>

#include "Player.h"
#include "Key.h"
#include "AudioManager.h"

using namespace std;

constexpr int kStartingNumberOfLives = 3;

Player::Player()
	: PlacableActor(0, 0)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_lives(kStartingNumberOfLives)
	, m_invincibilityCountdown(0)
{

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
