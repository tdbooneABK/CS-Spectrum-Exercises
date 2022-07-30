#include <iostream>
#include "Game.h"
#include "AudioManager.h"
#include "StateMachineExampleGame.h"

using namespace std;

int main()
{
	srand(time(0));
	Game myGame;

	StateMachineExampleGame gameStateMachine(&myGame);

	myGame.Initialize(&gameStateMachine);

	myGame.RunGameLoop();

	myGame.Deinitialize();

	AudioManager::DestroyInstance();

	return 0;
}