#include "Level01.h"
#include "GameButton.h"
#include "FileManager.h"
#include "AnimationTitle.h"

Level01::Level01()
{
	GameLevelManager::sGetInstance()->addLevel(1, this);
}

Level01::~Level01()
{
}

void Level01::enterLevel()
{
	mBtnStart = new GameButton(L"", 150.0f, 100.0f, FileManager::localization[0]);
	mStartEvent = new UStartEvent(this);
	mBtnStart->setBtnEvent(mStartEvent);

	mBtnSetting = new GameButton(L"", 150.0f, 100.0f, FileManager::localization[1]);
	mSettingEvent = new USetEvent(this);
	mBtnSetting->setBtnEvent(mSettingEvent);

	mBtnExit = new GameButton(L"", 150.0f, 100.0f, FileManager::localization[2]);
	mExitEvent = new UExitEvent(this);
	mBtnExit->setBtnEvent(mExitEvent);

	mBtnGameMode = new GameButton(L"", 200.0f, 100.0f, FileManager::localization[3]);
	mGameModeEvent = new UGmeModeEvent(this);
	mBtnGameMode->setBtnEvent(mGameModeEvent);

	mBtnEditMode = new GameButton(L"", 200.0f, 100.0f, FileManager::localization[4]);
	mEditEvent = new UEditModeEvent(this);
	mBtnEditMode->setBtnEvent(mEditEvent);

	mBtnCN = new GameButton(L"", 150.0f, 100.0f, FileManager::localization[5]);
	mCNEvent = new UCNEvent(this);
	mBtnCN->setBtnEvent(mCNEvent);

	mBtnEN = new GameButton(L"", 150.0f, 100.0f, FileManager::localization[6]);
	mENEvent = new UENEvent(this);
	mBtnEN->setBtnEvent(mENEvent);

	mBtnShutDown = new GameButton(L"", 75.0f, 75.0, FileManager::localization[7]);
	mShutDownEvent = new UShutDownEvent();
	mBtnShutDown->setBtnEvent(mShutDownEvent);

	mBtnReturn = new GameButton(L"", 75.0f, 75.0, FileManager::localization[8]);
	mReturnEvent = new UReturnEvent(this);
	mBtnReturn->setBtnEvent(mReturnEvent);

	mBtnCancel = new GameButton(L"", 150.0f, 75.0, FileManager::localization[9]);
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

	mCanvas = new AnimationTitle(0.0f, 0.0f, 6.0f, 6.0f, 3.0f, L"", Vector3(80.0f, 0.0f, 0.0f));
	mCanvas->setImageSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	mCanvas->setColor(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	mCompanyTitle = new AnimationTitle(WINDOW_WIDTH*0.5f - 256.0f, -174.0f, 6.0f, 6.0f, 3.0f, L"UI/company_title", Vector3(0.0f, 80.0f, 0.0f));
	mCompanyTitle->setImageSize(512.0f,174.0);

	mTeamTitle = new AnimationTitle(WINDOW_WIDTH*0.5f - 200.0f, WINDOW_HEIGHT, 6.0f, 6.0f, 3.0f, L"UI/team_title", Vector3(0.0f, -80.0f, 0.0f));
	mTeamTitle->setImageSize(400.0f, 162.0f);


	mState = CompanyTitle;
	mCompanyTitle->setEnable(true);
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
		case GameStart:
			return GameLevelManager::sGetInstance()->changeLevel(2);
			break;
		case EditStart:
			return GameLevelManager::sGetInstance()->changeLevel(3);
			break;
		case CompanyTitle:
			if (mCompanyTitle->isEnd())
			{
				mState = TeamTitle;
				mTeamTitle->setEnable(true);
				mCompanyTitle->destroy();
			}
			break;
		case TeamTitle:
			if (mTeamTitle->isEnd())
			{
				mState = Canvas;
				mCanvas->setEnable(true);
				mTeamTitle->destroy();
			}
			break;
		case Canvas:
			if (mCanvas->isEnd())
			{
				mState = MainMenu;
				mCanvas->destroy();
			}
			mBtnStart->setEnable(true);
			mBtnSetting->setEnable(true);
			mBtnExit->setEnable(true);
			break;
		}

	SceneManager::sGetInstance()->onLateUpdate(deltaTime);
	return this;
}

void Level01::leaveLevel()
{
	Engine::sGetInstance()->enableGameMode(false);

	mBtnStart->destroy();
	mBtnStart = nullptr;
	mBtnSetting->destroy();
	mBtnSetting = nullptr;
	mBtnExit->destroy();
	mBtnExit = nullptr;
	mBtnGameMode->destroy();
	mBtnGameMode = nullptr;
	mBtnEditMode->destroy();
	mBtnEditMode = nullptr;
	mBtnCN->destroy();
	mBtnCN = nullptr;
	mBtnEN->destroy();
	mBtnCN = nullptr;
	mBtnShutDown->destroy();
	mBtnShutDown = nullptr;
	mBtnReturn->destroy();;
	mBtnReturn = nullptr;
	mBtnCancel->destroy();
	mBtnCancel = nullptr;

	delete mStartEvent;
	mStartEvent = nullptr;
	delete mSettingEvent;
	mSettingEvent = nullptr;
	delete mExitEvent;
	mExitEvent = nullptr;
	delete mGameModeEvent;
	mGameModeEvent = nullptr;
	delete mEditEvent;
	mEditEvent = nullptr;
	delete mCNEvent;
	mCNEvent = nullptr;
	delete mENEvent;
	mENEvent = nullptr;
	delete mShutDownEvent;
	mShutDownEvent = nullptr;
	delete mReturnEvent;
	mReturnEvent = nullptr;
	delete mCancelEvent;
	mCancelEvent = nullptr;
}

void Level01::changeState(State s)
{
	mState = s;
}

void Level01::changeLanguage()
{
	mBtnStart->setText(FileManager::localization[0]);
	mBtnSetting->setText(FileManager::localization[1]);
	mBtnExit->setText(FileManager::localization[2]);
	mBtnGameMode->setText(FileManager::localization[3]);
	mBtnEditMode->setText(FileManager::localization[4]);
	mBtnCN->setText(FileManager::localization[5]);
	mBtnEN->setText(FileManager::localization[6]);
	mBtnShutDown->setText(FileManager::localization[7]);
	mBtnReturn->setText(FileManager::localization[8]);
	mBtnCancel->setText(FileManager::localization[9]);
}
