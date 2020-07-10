#include "ULevelEvent.h"
#include "Level01.h"
#include "GameLevelManager.h"
#include "Engine.h"
#include "FileManager.h"
#include "SoundManager.h"

void UStartEvent::onClick()
{
	SoundManager::sGetInstance()->playOnceAudio(12);
	reinterpret_cast<Level01*>(mLevel)->changeState(Level01::State::GameMode);
}

void USetEvent::onClick()
{
	SoundManager::sGetInstance()->playOnceAudio(12);
	reinterpret_cast<Level01*>(mLevel)->changeState(Level01::State::Setting);
}

void UExitEvent::onClick()
{
	SoundManager::sGetInstance()->playOnceAudio(12);
	reinterpret_cast<Level01*>(mLevel)->changeState(Level01::State::Exit);
}

void UGmeModeEvent::onClick()
{
	SoundManager::sGetInstance()->playOnceAudio(12);
	reinterpret_cast<Level01*>(mLevel)->changeState(Level01::State::GameStart);
}

void UEditModeEvent::onClick()
{
	SoundManager::sGetInstance()->playOnceAudio(12);
	reinterpret_cast<Level01*>(mLevel)->changeState(Level01::State::EditStart);
}

void UCNEvent::onClick()
{
	SoundManager::sGetInstance()->playOnceAudio(12);
	FileManager::changeLanguage(Language::CN);
	reinterpret_cast<Level01*>(mLevel)->changeLanguage();
}

void UENEvent::onClick()
{
	SoundManager::sGetInstance()->playOnceAudio(12);
	FileManager::changeLanguage(Language::US);
	reinterpret_cast<Level01*>(mLevel)->changeLanguage();
}

void UShutDownEvent::onClick()
{
	SoundManager::sGetInstance()->playOnceAudio(12);
	DestroyWindow(Engine::sGetInstance()->getHWND());
}

void UReturnEvent::onClick()
{
	SoundManager::sGetInstance()->playOnceAudio(13);
	reinterpret_cast<Level01*>(mLevel)->changeState(Level01::State::MainMenu);
}

void UCancelEvent::onClick()
{
	SoundManager::sGetInstance()->playOnceAudio(13);
	reinterpret_cast<Level01*>(mLevel)->changeState(Level01::State::MainMenu);
}
