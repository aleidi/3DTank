#include "Level01.h"
#include "GameButton.h"

Level01::Level01()
{
	GameLevelManager::sGetInstance()->addLevel(1, this);
}

Level01::~Level01()
{
}

void Level01::enterLevel()
{
	mBtnStart = new GameButton(L"", 150.0f, 100.0f, L"Start");
	mStartEvent = new UStartEvent(this);
	mBtnStart->setBtnEvent(mStartEvent);

	mBtnSetting = new GameButton(L"", 150.0f, 100.0f, L"Setting");
	mSettingEvent = new USetEvent(this);
	mBtnSetting->setBtnEvent(mSettingEvent);

	mBtnExit = new GameButton(L"", 150.0f, 100.0f, L"Exit");
	mExitEvent = new UExitEvent(this);
	mBtnExit->setBtnEvent(mExitEvent);

	mBtnGameMode = new GameButton(L"", 150.0f, 100.0f, L"GameMode");
	mGameModeEvent = new UGmeModeEvent();
	mBtnGameMode->setBtnEvent(mGameModeEvent);

	mBtnEditMode = new GameButton(L"", 150.0f, 100.0f, L"EditMode");
	mEditEvent = new UEditModeEvent();
	mBtnEditMode->setBtnEvent(mEditEvent);

	mBtnCN = new GameButton(L"", 150.0f, 100.0f, L"Chinese");
	mCNEvent = new UCNEvent();
	mBtnCN->setBtnEvent(mCNEvent);

	mBtnEN = new GameButton(L"", 150.0f, 100.0f, L"English");
	mENEvent = new UENEvent();
	mBtnEN->setBtnEvent(mENEvent);

	mBtnShutDown = new GameButton(L"", 75.0f, 75.0, L"Yes");
	mShutDownEvent = new UShutDownEvent();
	mBtnShutDown->setBtnEvent(mShutDownEvent);

	mBtnReturn = new GameButton(L"", 75.0f, 75.0, L"No");
	mReturnEvent = new UReturnEvent(this);
	mBtnReturn->setBtnEvent(mReturnEvent);

	mBtnCancel = new GameButton(L"", 150.0f, 75.0, L"Return");
	mCancelEvent = new UCancelEvent(this);
	mBtnCancel->setBtnEvent(mCancelEvent);

	//MainMenu
	mBtnStart->setPosition(WINDOW_WIDTH / 2 - 75.0f, WINDOW_HEIGHT * 1 / 2);
	mBtnStart->setTextPos(WINDOW_WIDTH / 2 - 35.0f, WINDOW_HEIGHT * 1 / 2 + 40.0f);
	mBtnSetting->setPosition(WINDOW_WIDTH / 2 - 75.0f, WINDOW_HEIGHT * 1 / 3 - 20.0f);
	mBtnSetting->setTextPos(WINDOW_WIDTH / 2 - 55.0f, WINDOW_HEIGHT * 1 / 3 - 20.0f + 40.0f);
	mBtnExit->setPosition(WINDOW_WIDTH / 2 - 75.0f, WINDOW_HEIGHT * 1 / 6 - 40.0f);
	mBtnExit->setTextPos(WINDOW_WIDTH / 2 - 35.0f, WINDOW_HEIGHT * 1 / 6 - 40.0f + 40.0f);
	//GameMode
	mBtnGameMode->setPosition(WINDOW_WIDTH / 2 - 75.0f, WINDOW_HEIGHT * 1 / 2);
	mBtnGameMode->setTextPos(WINDOW_WIDTH / 2 - 55.0f, WINDOW_HEIGHT * 1 / 2 + 40.0f);
	mBtnGameMode->setEnable(false);
	mBtnEditMode->setPosition(WINDOW_WIDTH / 2 - 75.0f, WINDOW_HEIGHT * 1 / 6);
	mBtnEditMode->setTextPos(WINDOW_WIDTH / 2 - 55.0f, WINDOW_HEIGHT * 1 / 6 + 40.0f);
	mBtnEditMode->setEnable(false);
	//Language
	mBtnCN->setPosition(WINDOW_WIDTH / 2 - 75.0f, WINDOW_HEIGHT * 1 / 2);
	mBtnCN->setTextPos(WINDOW_WIDTH / 2 - 55.0f, WINDOW_HEIGHT * 1 / 2 + 40.0f);
	mBtnCN->setEnable(false);
	mBtnEN->setPosition(WINDOW_WIDTH / 2 - 75.0f, WINDOW_HEIGHT * 1 / 6);
	mBtnEN->setTextPos(WINDOW_WIDTH / 2 - 55.0f, WINDOW_HEIGHT * 1 / 6 + 40.0f);
	mBtnEN->setEnable(false);
	//Select
	mBtnShutDown->setPosition(WINDOW_WIDTH / 3, WINDOW_HEIGHT * 1 / 2 - 25.0f);
	mBtnShutDown->setTextPos(WINDOW_WIDTH / 3 + 12.5f, WINDOW_HEIGHT * 1 / 2);
	mBtnShutDown->setEnable(false);
	mBtnReturn->setPosition(WINDOW_WIDTH * 2 / 3, WINDOW_HEIGHT * 1 / 2 - 25.0f);
	mBtnReturn->setTextPos(WINDOW_WIDTH * 2 / 3 + 18.5f, WINDOW_HEIGHT * 1 / 2);
	mBtnReturn->setEnable(false);
	//cancle
	mBtnCancel->setPosition(WINDOW_WIDTH - 200.0f, 50.0f);
	mBtnCancel->setTextPos(WINDOW_WIDTH - 180.0f, 75.0f);
	mBtnCancel->setEnable(false);


	mState = MainMenu;
}

GameLevelBase * Level01::onUpdate(float deltaTime)
{
	if (mCurrentGameMode != nullptr)
	{
	}

	if (DInputPC::getInstance().iskeyDown(DIK_F2))
	{
		return GameLevelManager::sGetInstance()->changeLevel(2);
	}

	switch (mState)
	{
		case MainMenu:
			mBtnStart->setEnable(true);
			mBtnSetting->setEnable(true);
			mBtnExit->setEnable(true);
			mBtnGameMode->setEnable(false);
			mBtnEditMode->setEnable(false);
			mBtnCN->setEnable(false);
			mBtnEN->setEnable(false);
			mBtnShutDown->setEnable(false);
			mBtnReturn->setEnable(false);
			mBtnCancel->setEnable(false);
			break;

		case GameMode:
			mBtnStart->setEnable(false);
			mBtnSetting->setEnable(false);
			mBtnExit->setEnable(false);
			mBtnGameMode->setEnable(true);
			mBtnEditMode->setEnable(true);
			mBtnCN->setEnable(false);
			mBtnEN->setEnable(false);
			mBtnShutDown->setEnable(false);
			mBtnReturn->setEnable(false);
			mBtnCancel->setEnable(true);
			break;

		case Setting:
			mBtnStart->setEnable(false);
			mBtnSetting->setEnable(false);
			mBtnExit->setEnable(false);
			mBtnGameMode->setEnable(false);
			mBtnEditMode->setEnable(false);
			mBtnCN->setEnable(true);
			mBtnEN->setEnable(true);
			mBtnShutDown->setEnable(false);
			mBtnReturn->setEnable(false);
			mBtnCancel->setEnable(true);
			break;

		case Exit:
			mBtnStart->setEnable(false);
			mBtnSetting->setEnable(false);
			mBtnExit->setEnable(false);
			mBtnGameMode->setEnable(false);
			mBtnEditMode->setEnable(false);
			mBtnCN->setEnable(false);
			mBtnEN->setEnable(false);
			mBtnShutDown->setEnable(true);
			mBtnReturn->setEnable(true);
			mBtnCancel->setEnable(false);
			break;
		}
	return this;
}

void Level01::leaveLevel()
{
}

void Level01::changeState(State s)
{
	mState = s;
}
