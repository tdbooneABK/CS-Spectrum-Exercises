#pragma once
#include <string>
#include "PlacableActor.h"
#include "Combatant.h"
#include "Inventory.h"

class Key;
class Invincibility;

class Player : public PlacableActor, public Combatant
{
public:
	Player(std::string name, WeaponType weaponType, ArmorClass armorClass);
	~Player();

	bool HasKey(ActorColor color);
	bool PickupKey(Key* key);
	bool UseKey(ActorColor color);
	Key* GetKey() { return m_pCurrentKey; }
	Inventory* GetInventory() { return m_Inventory; }

	bool IsInvincible();
	void PickupInvincibililty();

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	bool IsAlive();

	virtual ActorType GetType() override { return ActorType::Player; }
	virtual void Draw() override;
	virtual void Update() override;
private:
	Key* m_pCurrentKey;
	int m_money;
	int m_invincibilityCountdown;
	Inventory* m_Inventory;
};
