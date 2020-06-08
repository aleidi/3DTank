#include "GameModeBase.h"

GameModeBase::GameModeBase()
	:mGameState(),mPlayer(),mPlayerController()
{
}

GameModeBase::~GameModeBase()
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
