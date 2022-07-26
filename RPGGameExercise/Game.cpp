#include "Game.h"
#include "Player.h"
#include "PlayerInfoDialog.h"
#include "Enemy.h"
#include "Encounter.h"

Game::Game()
	: m_player(PlayerInfoDialog().GetPlayerInfo())
{}

Game::~Game() {
	delete m_player;
	m_player = nullptr;
}

void Game::Run()
{
	Enemy enemy = Enemy();
	Encounter encounter = Encounter(*m_player, enemy);
	encounter.Run();
}
