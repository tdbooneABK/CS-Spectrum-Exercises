#pragma once
#include <atomic>
#include <thread>

enum class InputEvent {
	None,
	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight,
	OpenInventory,
	ExitGame
};

class InputProcessor
{
	std::atomic<bool> m_ThreadShouldRun;
	std::atomic<InputEvent> m_CapturedEvent;
	std::thread* m_InputThread;

public:
	InputProcessor();
	~InputProcessor();
	void Run();
	void Stop();
	// TODO: Figure out how to do this, so we're not moving
	// when the inventory menu is open? Is that a concern?
	//void Pause();
	//void Resume();
	InputEvent GetInput();
private:
	void ListenForKeyPress();
};

