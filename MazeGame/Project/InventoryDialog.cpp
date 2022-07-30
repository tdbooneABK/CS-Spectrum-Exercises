#include <iostream>
#include "InventoryDialog.h"

InventoryDialog::InventoryDialog(Inventory* inventory)
	: m_Inventory(inventory)
	, m_State(InventoryDialogState::SelectingOption)
{
}

InventoryDialog::~InventoryDialog()
{

}

void InventoryDialog::Run() {
	while (m_State != InventoryDialogState::Exiting) {
		system("cls");
		DrawInventory();
		switch (m_State) {
		case InventoryDialogState::SelectingOption:
			GetOption();
			break;
		case InventoryDialogState::DroppingItem:
			DropItem();
			break;
		case InventoryDialogState::EquippingWeapon:
			EquipWeapon();
			break;
		}
	}
	system("cls");
}

void InventoryDialog::GetOption() {
	std::cout << "What would you like to do?" << std::endl;
	std::cout << "1) Drop an item" << std::endl;
	std::cout << "2) Equip a weapon" << std::endl;
	std::cout << "3) Exit inventory" << std::endl;
	int selection = 0;
	std::cin >> selection;
	switch (selection) {
	case 1:
		m_State = InventoryDialogState::DroppingItem;
		break;
	case 2:
		m_State = InventoryDialogState::EquippingWeapon;
		break;
	case 3:
	default:
		m_State = InventoryDialogState::Exiting;
		break;
	}
}

void InventoryDialog::DropItem() {
	std::cout << "Which item would you like to drop?" << std::endl;
	std::cout << "(Pretend this works)" << std::endl;
	int selection = 0;
	std::cin >> selection;
	m_State = InventoryDialogState::SelectingOption;
}

void InventoryDialog::EquipWeapon() {
	std::cout << "Which weapon would you like to equip?" << std::endl;
	std::cout << "(Pretend this works)" << std::endl;
	int selection = 0;
	std::cin >> selection;
	m_State = InventoryDialogState::SelectingOption;
}

void InventoryDialog::DrawInventory()
{
	std::cout << "Inventory:" << std::endl;
	for (int i = 0; i < Inventory::k_inventorySize; i++) {
		std::string itemName = "empty";
		if (m_Inventory->GetInventoryItem(i)) {
			itemName = m_Inventory->GetInventoryItem(i)->GetName();
		}
		std::cout << i + 1 << ") " << itemName << std::endl;
	}
	std::cout << std::endl;
}
