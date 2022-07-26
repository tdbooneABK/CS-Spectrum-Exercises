#pragma once
#include "PlacableActor.h"

class Key;
class Invincibility;

class Player : public PlacableActor
{
public:
	Player();

	bool HasKey();
	bool HasKey(ActorColor color);
	bool IsInvincible();
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();
	Key* GetKey() { return m_pCurrentKey; }
	void PickupInvincibililty();

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	int GetLives() { return m_lives; }
	void DecrementLives() { m_lives--; }

	virtual ActorType GetType() override { return ActorType::Player; }
	virtual void Draw() override;
	virtual void Update() override;
private:
	Key* m_pCurrentKey;
	int m_money;
	int m_lives;
	int m_invincibilityCountdown;
};
