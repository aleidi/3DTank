#include "ULevelEvent.h"
#include "Level01.h"
#include "GameLevelManager.h"
#include "Engine.h"
#include "FileManager.h"

void UStartEvent::onClick()
{
	reinterpret_cast<Level01*>(mLevel)->changeState(Level01::State::GameMode);
}

void USetEvent::onClick()
{
	reinterpret_cast<Level01*>(mLevel)->changeState(Level01::State::Setting);
}

void UExitEvent::onClick()
{
	reinterpret_cast<Level01*>(mLevel)->changeState(Level01::State::Exit);
}

void UGmeModeEvent::onClick()
{
	GameLevelManager::sGetInstance()->changeLevel(1);
}

void UEditModeEvent::onClick()
{
	GameLevelManager::sGetInstance()->changeLevel(2);
}

void UCNEvent::onClick()
{
	FileManager::changeLanguage(Language::CN);
	reinterpret_cast<Level01*>(mLevel)->changeLanguage();
}

void UENEvent::onClick()
{
	FileManager::changeLanguage(Language::US);
	reinterpret_cast<Level01*>(mLevel)->changeLanguage();
}

void UShutDownEvent::onClick()
{
	DestroyWindow(Engine::sGetInstance()->getHWND());
}

void UReturnEvent::onClick()
{
	reinterpret_cast<Level01*>(mLevel)->changeState(Level01::State::MainMenu);
}

void UCancelEvent::onClick()
{
	reinterpret_cast<Level01*>(mLevel)->changeState(Level01::State::MainMenu);
}
