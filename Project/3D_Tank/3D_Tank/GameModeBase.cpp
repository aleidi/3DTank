#include "GameModeBase.h"
#include "ControllerBase.h"
#include "DefaultPlayer.h"
#include "DefaultPlayerController.h"
#include "GameCommon.h"

GameModeBase* GameModeBase::MainGameMode = nullptr;

GameModeBase::GameModeBase()
	:mGameState(),mPlayer(),mPlayerController()
{
	MainGameMode = this;
}

GameModeBase::~GameModeBase()
{
	SceneManager::sGetInstance()->removeGameObjectFromPool(mPlayer);
	mPlayer = nullptr;
	SceneManager::sGetInstance()->removeGameObjectFromPool(mPlayerController);
	mPlayerController = nullptr;

	MainGameMode = nullptr;
}

void GameModeBase::onInit()
{
	if (mPlayer == nullptr && mPlayerController == nullptr)
	{
		mPlayer = new DefaultPlayer();
		mPlayerController = new DefaultPlayerController();
		mPlayerController->posses(mPlayer);
	}
}

void GameModeBase::onUpdate(float deltaTime)
{
}

void GameModeBase::setGameState(GameStateBase * gameState) noexcept
{
	mGameState = gameState;
}

void GameModeBase::setPlayer(Pawn * player) noexcept
{
	mPlayer = player;
}

void GameModeBase::setPlayerController(ControllerBase * playerController) noexcept
{
	mPlayerController = playerController;
}

Pawn * GameModeBase::getPlayer() const
{
	return mPlayer;
}

ControllerBase * GameModeBase::getPlayerController() const
{
	return mPlayerController;
}
