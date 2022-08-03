#pragma once
#include <string>

enum class ItemType {
	Key,
	Weapon
};

class InventoryItem
{
public:
	InventoryItem()
	{

	}
	virtual ~InventoryItem()
	{

	}

	virtual std::string GetName() = 0;
	virtual ItemType GetType() = 0;
};
