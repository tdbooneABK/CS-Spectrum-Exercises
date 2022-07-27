#pragma once
#include <string>
#include "PlacableActor.h"
#include "Armor.h"
#include "Weapon.h"

class Key;
class Invincibility;

class Player : public PlacableActor
{
public:
	Player(std::string name, WeaponType weaponType, ArmorClass armorClass);
	~Player();

	std::string GetName() { return m_Name; }

	bool HasKey();
	bool HasKey(ActorColor color);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();
	Key* GetKey() { return m_pCurrentKey; }

	Weapon* GetWeapon() { return m_pCurrentWeapon; }

	Armor* GetArmor() { return m_pCurrentArmor; }
	
	bool IsInvincible();
	void PickupInvincibililty();

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	int GetHealth() { return m_health; }
	void ApplyDamage(int damageAmount);
	bool IsAlive();

	virtual ActorType GetType() override { return ActorType::Player; }
	virtual void Draw() override;
	virtual void Update() override;
private:
	std::string m_Name;
	Key* m_pCurrentKey;
	Weapon* m_pCurrentWeapon;
	Armor* m_pCurrentArmor;
	int m_money;
	int m_health;
	int m_invincibilityCountdown;
};
