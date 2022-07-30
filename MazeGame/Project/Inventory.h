#pragma once
#include "InventoryItem.h"

class Inventory
{
	InventoryItem** m_inventoryItems;
public:
	Inventory();
	~Inventory();
	static const int k_inventorySize = 6;
	InventoryItem* GetInventoryItem(int i, bool removeItem = false);
	InventoryItem* DropItem(int itemIndex);
	bool AddItem(InventoryItem* itemToAdd);
};
