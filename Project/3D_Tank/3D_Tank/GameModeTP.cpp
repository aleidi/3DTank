#include "GameModeTP.h"
#include "PlayerTank.h"
#include "PlayerController.h"
#include "GameCommon.h"

GameModeTP::GameModeTP()
	:GameModeBase()
{
	mPlayer = new PlayerTank();
	mPlayerController = new PlayerController();
	mPlayerController->posses(mPlayer);
}

GameModeTP::~GameModeTP()
{
}

void GameModeTP::onInit()
{
}
