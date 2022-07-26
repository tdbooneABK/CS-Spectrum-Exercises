#include <iostream>
#include "RestDialog.h"
#include "Player.h"

RestDialog::RestDialog(Player* playerPt)
	: m_hasRested(false), m_playerPt(playerPt)
{}

RestDialog::~RestDialog()
{}

bool RestDialog::Run() {
	int inputValue = 0;

	do {
		system("cls");
		PrintPlayerInfo();
		DrawOptions();
		std::cin >> inputValue;
		if (inputValue == 1) {
			Rest();
		}
	} while (inputValue != 2 && inputValue != 3);

	if (inputValue == 2) {
		return true;
	}
	else {
		return false;
	}
}

void RestDialog::PrintPlayerInfo() {
	std::cout << "Player Info:" << std::endl;
	std::cout << "Name: " << m_playerPt->GetName() << std::endl;
	std::cout << "Health: " << m_playerPt->GetHealth() << std::endl;
	std::cout << "Weapon: " << m_playerPt->GetWeapon().GetWeaponName() << std::endl;
	std::cout << "Armor: " << m_playerPt->GetArmor().GetArmorName() << std::endl;
}

void RestDialog::DrawOptions() {
	std::cout << std::endl << "What would you like to do?" << std::endl << std::endl;
	if (!m_hasRested) {
		std::cout << "1) Rest for a while and heal your injuries" << std::endl;
	}
	std::cout << "2) Continue searching for monsters and treasure" << std::endl;
	std::cout << "3) Retire from adventuring" << std::endl;
}

void RestDialog::Rest() {
	m_playerPt->AddHealth(20);
	m_hasRested = true;
}
