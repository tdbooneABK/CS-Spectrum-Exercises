#include "Game.h"
#include "Player.h"
#include "PlayerInfoDialog.h"
#include "Enemy.h"
#include "Encounter.h"
#include "RestDialog.h"
#include <iostream>

Game::Game()
{}

Game::~Game()
{}

void Game::Run()
{
	Player* playerPt = (PlayerInfoDialog().GetPlayerInfo());
	bool continueAdventuring = true;
	do {
		Enemy enemy = Enemy();
		Encounter encounter = Encounter(playerPt, &enemy);
		encounter.Run();
		if (playerPt->GetHealth() > 0) {
			continueAdventuring = RestDialog(playerPt).Run();
			// This prevents the end of the rest dialog input from skipping the first part of the encounter output
			std::cin.ignore();
		}
		else {
			continueAdventuring = false;
		}
	} while (continueAdventuring);

	delete playerPt;
	playerPt = nullptr;
}
