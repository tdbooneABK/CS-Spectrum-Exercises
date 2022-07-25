#include <iostream>
#include "PlayerInfoDialog.h"
#include "Player.h"
#include "Weapon.h"

/*
	Rather than returning a Player object, this should either accept an empty Player and populate the values,
	or it should use "new" return a _pointer_ to a player object.
*/
Player PlayerInfoDialog::GetPlayerInfo() {
	std::string inputName = "";
	int inputWeapon = 0;
	int inputArmorClass = 0;
	
	inputName = GetPlayerName();
	inputWeapon = GetWeapon();
	inputArmorClass = GetArmorClass();
	Player newPlayer = Player(inputName, (WeaponType)inputWeapon, inputArmorClass);
	PrintPlayerInfo(newPlayer);
	return newPlayer;
}

std::string PlayerInfoDialog::GetPlayerName() {
	std::string inputString = "";
	std::cout << "Please enter your character name:" << std::endl;
	std::cin >> inputString;
	return inputString;
}

int PlayerInfoDialog::GetWeapon() {
	std::cout << std::endl << "Please select your weapon:" << std::endl;
	for (int i = 1; i <= Weapon::maxWeaponType; i++) {
		std::cout << i << ") " << Weapon::GetWeaponName((WeaponType)i) << std::endl;
	}

	int inputWeapon = 0;

	do {
		std::cin >> inputWeapon;
		if (std::cin.fail()) {
			std::cout << "Invalid input! Please enter a number." << std::endl;
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		else if (inputWeapon > 0 && inputWeapon <= Weapon::maxWeaponType) {
			return inputWeapon;
		}
		else {
			std::cout << "Invalid weapon! Please enter a number between 1 and 3." << std::endl;
		}
	} while (true);
}

int PlayerInfoDialog::GetArmorClass() {
	std::cout << std::endl << "Please select your armor class:" << std::endl;
	std::cout << "1) Light" << std::endl;
	std::cout << "2) Medium" << std::endl;
	std::cout << "3) Heavy" << std::endl;

	int inputArmorClass = 0;

	do {
		std::cin >> inputArmorClass;
		if (std::cin.fail()) {
			std::cout << "Invalid input! Please enter a number." << std::endl;
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		else if (inputArmorClass > 0 && inputArmorClass <= 3) {
			return inputArmorClass;
		}
		else {
			std::cout << "Invalid armor class! Please enter a number between 1 and 3." << std::endl;
		}
	} while (true);
}

void PlayerInfoDialog::PrintPlayerInfo(Player player) {
	system("cls");
	std::cout << "Player Info:" << std::endl;
	std::cout << "Name: " << player.GetName() << std::endl;
	std::cout << "Health: " << player.GetHealth() << std::endl;
	std::cout << "Weapon: " << player.GetWeapon().GetWeaponName() << std::endl;

	std::string armorDisplayName = "";
	switch (player.GetArmorClass()) {
	case 1:
		armorDisplayName = "Light";
		break;
	case 2:
		armorDisplayName = "Medium";
		break;
	case 3:
		armorDisplayName = "Heavy";
		break;
	}
	std::cout << "Armor: " << armorDisplayName << " Armor" << std::endl;
	std::cout << std::endl << "Press enter to continue..." << std::endl;
	std::cin.ignore();
	std::cin.get();
}