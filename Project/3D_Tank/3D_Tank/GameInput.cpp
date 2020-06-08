#include <assert.h>
#include "GameInput.h"

GameInput* GameInput::sInstance = nullptr;

GameInput * GameInput::sGetInstance()
{
	return sInstance;
}

void GameInput::creataSingleton()
{
	assert(!sInstance);
	sInstance = new GameInput();
}

void GameInput::destroy()
{
	delete sInstance;
	sInstance = nullptr;
}

bool GameInput::onInit()
{
	return true;
}

bool GameInput::onUpdate(float deltaTime)
{
	return true;
}

GameInput::GameInput()
{
}

GameInput::~GameInput()
{
}
