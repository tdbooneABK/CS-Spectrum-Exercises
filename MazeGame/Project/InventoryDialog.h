#pragma once
#include "Inventory.h"

enum class InventoryDialogState {
	SelectingOption,
	DroppingItem,
	EquippingWeapon,
	Exiting
};

class InventoryDialog
{
public:
	InventoryDialog(Inventory* inventory);
	~InventoryDialog();
	void Run();

private:
	Inventory* m_Inventory;
	InventoryDialogState m_State;

	void DrawInventory();
	void GetOption();
	void DropItem();
	void EquipWeapon();
};
