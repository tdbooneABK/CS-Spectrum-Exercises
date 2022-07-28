#include "GameplayState.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <assert.h>

#include "Enemy.h"
#include "Monster.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Invincibility.h"
#include "Goal.h"
#include "AudioManager.h"
#include "Utility.h"
#include "StateMachineExampleGame.h"
#include "PlayerInfoDialog.h"
#include "Encounter.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
	: m_pPlayer(PlayerInfoDialog().GetPlayerInfo())
	, m_pOwner(pOwner)
	, m_beatLevel(false)
	, m_skipFrameCount(0)
	, m_currentLevel(0)
	, m_pLevel(nullptr)
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
}

bool GameplayState::Update(bool processInput)
{
	if (processInput && !m_beatLevel)
	{
		int input = _getch();
		int arrowInput = 0;
		int newPlayerX = m_pPlayer->GetXPosition();
		int newPlayerY = m_pPlayer->GetYPosition();

		// One of the arrow keys were pressed
		if (input == kArrowInput)
		{
			arrowInput = _getch();
		}

		if ((input == kArrowInput && arrowInput == kLeftArrow) ||
			(char)input == 'A' || (char)input == 'a')
		{
			newPlayerX--;
		}
		else if ((input == kArrowInput && arrowInput == kRightArrow) ||
			(char)input == 'D' || (char)input == 'd')
		{
			newPlayerX++;
		}
		else if ((input == kArrowInput && arrowInput == kUpArrow) ||
			(char)input == 'W' || (char)input == 'w')
		{
			newPlayerY--;
		}
		else if ((input == kArrowInput && arrowInput == kDownArrow) ||
			(char)input == 'S' || (char)input == 's')
		{
			newPlayerY++;
		}
		else if (input == kEscapeKey)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
		}
		else if ((char)input == 'Z' || (char)input == 'z')
		{
			m_pPlayer->DropKey();
		}

		m_pPlayer->Update();
		// If position never changed
		if (newPlayerX == m_pPlayer->GetXPosition() && newPlayerY == m_pPlayer->GetYPosition())
		{
			//return false;
		}
		else
		{
			HandleCollision(newPlayerX, newPlayerY);
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

	return false;
}

void GameplayState::HandleCollision(int newPlayerX, int newPlayerY)
{
	PlacableActor* collidedActor = m_pLevel->UpdateActors(newPlayerX, newPlayerY);
	if (collidedActor != nullptr && collidedActor->IsActive())
	{
		switch (collidedActor->GetType())
		{
		case ActorType::Enemy:
		{
			Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
			assert(collidedEnemy);
			AudioManager::GetInstance()->PlayLoseLivesSound();
			collidedEnemy->Remove();
			m_pPlayer->SetPosition(newPlayerX, newPlayerY);

			if (!m_pPlayer->IsInvincible()) {
				m_pPlayer->ApplyDamage(40);
				if (! m_pPlayer->IsAlive())
				{
					//TODO: Go to game over screen
					AudioManager::GetInstance()->PlayLoseSound();
					m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
				}
			}
			break;
		}
		case ActorType::Monster:
		{
			Monster* collidedMonster = dynamic_cast<Monster*>(collidedActor);
			assert(collidedMonster);
			if (!Encounter(m_pPlayer, collidedMonster).Run()) {
				AudioManager::GetInstance()->PlayLoseSound();
				m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
			}
			else {
				collidedMonster->Remove();
				m_pPlayer->SetPosition(newPlayerX, newPlayerY);
			}
			break;
		}
		case ActorType::Money:
		{
			Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
			assert(collidedMoney);
			AudioManager::GetInstance()->PlayMoneySound();
			collidedMoney->Remove();
			m_pPlayer->AddMoney(collidedMoney->GetWorth());
			m_pPlayer->SetPosition(newPlayerX, newPlayerY);
			break;
		}
		case ActorType::Invincibility:
		{
			Invincibility* invincibilityPowerup = dynamic_cast<Invincibility*>(collidedActor);
			assert(invincibilityPowerup);
			invincibilityPowerup->Remove();
			m_pPlayer->PickupInvincibililty();
			m_pPlayer->SetPosition(newPlayerX, newPlayerY);
			break;
		}
		case ActorType::Key:
		{
			Key* collidedKey = dynamic_cast<Key*>(collidedActor);
			assert(collidedKey);
			if (!m_pPlayer->HasKey())
			{
				m_pPlayer->PickupKey(collidedKey);
				collidedKey->Remove();
				m_pPlayer->SetPosition(newPlayerX, newPlayerY);
				AudioManager::GetInstance()->PlayKeyPickupSound();
			}
			break;
		}
		case ActorType::Door:
		{
			Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
			assert(collidedDoor);
			if (!collidedDoor->IsOpen())
			{
				if (m_pPlayer->HasKey(collidedDoor->GetColor()))
				{
					collidedDoor->Open();
					collidedDoor->Remove();
					m_pPlayer->UseKey();
					m_pPlayer->SetPosition(newPlayerX, newPlayerY);
					AudioManager::GetInstance()->PlayDoorOpenSound();
				}
				else
				{
					AudioManager::GetInstance()->PlayDoorClosedSound();
				}
			}
			else
			{
				m_pPlayer->SetPosition(newPlayerX, newPlayerY);
			}
			break;
		}
		case ActorType::Goal:
		{
			Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
			assert(collidedGoal);
			collidedGoal->Remove();
			m_pPlayer->SetPosition(newPlayerX, newPlayerY);
			m_beatLevel = true;
			break;
		}
		default:
			break;
		}
	}
	else if (m_pLevel->IsSpace(newPlayerX, newPlayerY)) // no collision
	{
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

	// Top Border
	for (int i = 0; i < m_pLevel->GetWidth(); ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;

	// Left Side border
	cout << Level::WAL;

	cout << " wasd-move " << Level::WAL << " z-drop key " << Level::WAL;

	cout << " $:" << m_pPlayer->GetMoney() << " " << Level::WAL;
	cout << " health:" << m_pPlayer->GetHealth() << " " << Level::WAL;
	cout << " key:";
	if (m_pPlayer->HasKey())
	{
		m_pPlayer->GetKey()->Draw();
	}
	else
	{
		cout << " ";
	}

	// RightSide border
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);

	COORD pos;
	pos.X = m_pLevel->GetWidth() - 1;
	pos.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(console, pos);

	cout << Level::WAL;
	cout << endl;

	// Bottom Border
	for (int i = 0; i < m_pLevel->GetWidth(); ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;
}