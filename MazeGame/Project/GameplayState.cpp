#include "GameplayState.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <assert.h>

#include "AudioManager.h"
#include "Utility.h"
#include "StateMachineExampleGame.h"
#include "PlayerInfoDialog.h"
#include "InventoryDialog.h"
#include "InputProcessor.h"

using namespace std;

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
	: m_pPlayer(PlayerInfoDialog().GetPlayerInfo())
	, m_pOwner(pOwner)
	, m_beatLevel(false)
	, m_skipFrameCount(0)
	, m_currentLevel(0)
	, m_pLevel(nullptr)
	, m_pInputProcessor(new InputProcessor())
{
	m_LevelNames.push_back("Level1.txt");
	m_LevelNames.push_back("Level2.txt");
	m_LevelNames.push_back("LevelA.txt");
	m_LevelNames.push_back("Level3.txt");
}

GameplayState::~GameplayState()
{
	delete m_pLevel;
	m_pLevel = nullptr;
	delete m_pPlayer;
	m_pPlayer = nullptr;

	m_pInputProcessor->Stop();
	delete m_pInputProcessor;
	m_pInputProcessor = nullptr;
}

bool GameplayState::Load()
{
	if (m_pLevel)
	{
		delete m_pLevel;
		m_pLevel = nullptr;
	}

	m_pLevel = new Level();
	
	return m_pLevel->Load(m_LevelNames.at(m_currentLevel), m_pPlayer->GetXPositionPointer(), m_pPlayer->GetYPositionPointer());

}

void GameplayState::Enter()
{
	Load();
	m_pInputProcessor->Run();
}

bool GameplayState::Update(bool processInput)
{
	if (processInput && !m_beatLevel)
	{
		int newPlayerX = m_pPlayer->GetXPosition();
		int newPlayerY = m_pPlayer->GetYPosition();

		switch (m_pInputProcessor->GetInput()) {
		case InputEvent::MoveUp:
			newPlayerY--;
			break;
		case InputEvent::MoveDown:
			newPlayerY++;
			break;
		case InputEvent::MoveLeft:
			newPlayerX--;
			break;
		case InputEvent::MoveRight:
			newPlayerX++;
			break;
		case InputEvent::OpenInventory:
			InventoryDialog(m_pPlayer->GetInventory()).Run();
			break;
		case InputEvent::ExitGame:
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
			break;
		}

		m_pPlayer->Update();
		HandleCollision(newPlayerX, newPlayerY);

		if (!m_pPlayer->IsAlive())
		{
			//TODO: Go to game over screen
			AudioManager::GetInstance()->PlayLoseSound();
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
		}
		else if (m_pPlayer->HasReachedExit()) {
			m_beatLevel = true;
			m_pPlayer->ResetLevelExitState();
		}
	}
	if (m_beatLevel)
	{
		++m_skipFrameCount;
		if (m_skipFrameCount > kFramesToSkip)
		{
			m_beatLevel = false;
			m_skipFrameCount = 0;
			++m_currentLevel;
			if (m_currentLevel == m_LevelNames.size())
			{
				Utility::WriteHighScore(m_pPlayer->GetMoney());

				AudioManager::GetInstance()->PlayWinSound();
				
				m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
			}
			else
			{
				// On to the next level
				system("cls");
				Load();
			}

		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	return false;
}

void GameplayState::HandleCollision(int newPlayerX, int newPlayerY)
{
	PlacableActor* collidedActor = m_pLevel->UpdateActors(newPlayerX, newPlayerY);
	if (collidedActor != nullptr && collidedActor->IsActive())
	{
		collidedActor->HandlePlayerCollision(m_pPlayer);
	}
	else if (m_pLevel->IsSpace(newPlayerX, newPlayerY))
	{
		// no collision
		m_pPlayer->SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_pLevel->IsWall(newPlayerX, newPlayerY))
	{
		// wall collision, do nothing
	}
}

void GameplayState::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	m_pLevel->Draw();

	// Set cursor position for player 
	COORD actorCursorPosition;
	actorCursorPosition.X = m_pPlayer->GetXPosition();
	actorCursorPosition.Y = m_pPlayer->GetYPosition();
	SetConsoleCursorPosition(console, actorCursorPosition);
	m_pPlayer->Draw();

	// Set the cursor to the end of the level
	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_pLevel->GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

	DrawHUD(console);
}

void GameplayState::DrawHUD(const HANDLE& console)
{
	cout << endl;

	const int hudWidth = 55;

	// Top Border
	for (int i = 0; i < hudWidth; ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);

	cout << Level::WAL << " " << m_pPlayer->GetName() << " " << Level::WAL << " " << m_pPlayer->GetWeapon()->GetWeaponName() << " " << Level::WAL;
	cout << " " << m_pPlayer->GetArmor()->GetArmorName() << " " << Level::WAL;

	COORD pos;
	pos.X = hudWidth - 1;
	pos.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(console, pos);
	cout << Level::WAL;
	cout << endl;

	for (int i = 0; i < hudWidth; ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;

	// Left Side border
	cout << Level::WAL;

	cout << " wasd-move " << Level::WAL << " z-open inventory " << Level::WAL;

	cout << " $:" << m_pPlayer->GetMoney() << " " << Level::WAL;
	cout << " health:" << m_pPlayer->GetHealth();

	// RightSide border

	GetConsoleScreenBufferInfo(console, &csbi);
	pos.X = hudWidth - 1;
	pos.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(console, pos);

	cout << Level::WAL;
	cout << endl;

	// Bottom Border
	for (int i = 0; i < hudWidth; ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;
}