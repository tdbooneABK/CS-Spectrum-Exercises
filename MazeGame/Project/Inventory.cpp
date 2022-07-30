#include "Inventory.h"

Inventory::Inventory()
	: m_inventoryItems(new InventoryItem* [Inventory::k_inventorySize])
{
	for (int i = 0; i < Inventory::k_inventorySize; i++) {
		m_inventoryItems[i] = nullptr;
	}
}

Inventory::~Inventory()
{
	for (int i = 0; i < Inventory::k_inventorySize; i++) {
		if (m_inventoryItems[i] != nullptr) {
			delete m_inventoryItems[i];
			m_inventoryItems[i] = nullptr;
		}
	}
	delete[] m_inventoryItems;
	m_inventoryItems = nullptr;
}

InventoryItem* Inventory::GetInventoryItem(int i, bool removeItem) {
	InventoryItem* itemPtr = m_inventoryItems[i];
	if (removeItem) {
		m_inventoryItems[i] = nullptr;
	}
	return itemPtr;
}

InventoryItem* Inventory::DropItem(int itemIndex) {
	InventoryItem* droppedItem = m_inventoryItems[itemIndex];
	m_inventoryItems[itemIndex] = nullptr;
	return droppedItem;
}

bool Inventory::AddItem(InventoryItem* itemToAdd) {
	for (int i = 0; i < Inventory::k_inventorySize; i++) {
		if (!m_inventoryItems[i]) {
			m_inventoryItems[i] = itemToAdd;
			return true;
		}
	}
	return false;
}
