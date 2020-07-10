#include <thread>

#include "Level01.h"
#include "GameButton.h"
#include "FileManager.h"
#include "AnimationTitle.h"
#include "RenderManager.h"
#include "ParticleSystem.h"
#include "GameCommon.h"
#include "FadeInOut.h"
#include "SoundManager.h"

Level01::Level01()
	: mCamTrig(false),mState(Empty)
{
	GameLevelManager::sGetInstance()->addLevel(1, this);
}

Level01::~Level01()
{
}

void Level01::enterLevel()
{
	std::thread t(&Level01::loadResource, this);
	t.detach();

	std::thread t2(&Level01::loadParticle, this);
	t2.detach();

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
	mBtnEditMode->setPosition(WINDOW_WIDTH / 2 - 75.0f, WINDOW_HEIGHT * 1 / 6);
	mBtnEditMode->setTextPos(WINDOW_WIDTH / 2 - 55.0f, WINDOW_HEIGHT * 1 / 6 + 40.0f);
	//Language
	mBtnCN->setPosition(WINDOW_WIDTH / 2 - 75.0f, WINDOW_HEIGHT * 1 / 2);
	mBtnCN->setTextPos(WINDOW_WIDTH / 2 - 55.0f, WINDOW_HEIGHT * 1 / 2 + 40.0f);
	mBtnEN->setPosition(WINDOW_WIDTH / 2 - 75.0f, WINDOW_HEIGHT * 1 / 6);
	mBtnEN->setTextPos(WINDOW_WIDTH / 2 - 55.0f, WINDOW_HEIGHT * 1 / 6 + 40.0f);
	//Select
	mBtnShutDown->setPosition(WINDOW_WIDTH / 3, WINDOW_HEIGHT * 1 / 2 - 25.0f);
	mBtnShutDown->setTextPos(WINDOW_WIDTH / 3 + 12.5f, WINDOW_HEIGHT * 1 / 2);
	mBtnReturn->setPosition(WINDOW_WIDTH * 2 / 3, WINDOW_HEIGHT * 1 / 2 - 25.0f);
	mBtnReturn->setTextPos(WINDOW_WIDTH * 2 / 3 + 18.5f, WINDOW_HEIGHT * 1 / 2);
	//cancle
	mBtnCancel->setPosition(WINDOW_WIDTH - 200.0f, 50.0f);
	mBtnCancel->setTextPos(WINDOW_WIDTH - 180.0f, 75.0f);

	mCanvas = new AnimationTitle(0.0f, 0.0f, 6.0f, 10.0f, 0.0f, L"", Vector3(160.0f, 0.0f, 0.0f));
	mCanvas->setImageSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	mCanvas->setColor(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	mCompanyTitle = new AnimationTitle(WINDOW_WIDTH*0.5f - 256.0f, -174.0f, 6.0f, 6.0f, 3.0f, L"UI/company_title", Vector3(0.0f, 80.0f, 0.0f));
	mCompanyTitle->setImageSize(512.0f,174.0);

	mTeamTitle = new AnimationTitle(WINDOW_WIDTH*0.5f - 200.0f, WINDOW_HEIGHT, 6.0f, 6.0f, 3.0f, L"UI/team_title", Vector3(0.0f, -80.0f, 0.0f));
	mTeamTitle->setImageSize(400.0f, 162.0f);

	mFadeInImage = new FadeInOut(L"UI/FadeBlack", WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f, 5.0f, FadeInOut::Type::FadeIn);

	//mCurrentGameMode = new GameModeBase();
	//mCurrentGameMode->onInit();
	//GameInstance::sGetInstance()->getPlayerController()->setEnable(true);

	mCompanyTitle->setEnable(true);
	mCanStart = true;
}

GameLevelBase * Level01::onUpdate(float deltaTime)
{

	SceneManager::sGetInstance()->onUpdate(deltaTime);



	if (mCurrentGameMode != nullptr)
	{
	}

	//if (DInputPC::getInstance().iskeyDown(DIK_F2))
	//{
	//	return GameLevelManager::sGetInstance()->changeLevel(2);
	//}

	if (mCamFollower != nullptr)
	{

		float angle = Vector3::lengthSq(mCamFollower->getTransform()->Forward, mExhibition->getTransform()->Forward);

		if (angle < 0.1f)
		{
			mCamTrig = !mCamTrig;
		}

		if (!mCamTrig)
		{
			mCamFollower->getTransform()->rotateY(deltaTime* 3.0f);
		}
		else
		{
			mCamFollower->getTransform()->rotateZ(deltaTime* 3.0f);
		}
	}


	RenderManager::sGetInstance()->rotateLight(0.0f, deltaTime*20.0f, 0.0f);

	switch (mState)
	{
		case MainMenu:
			if (!mIsLoadFin)
			{
				return this;
			}
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
			mState = LoadingGame;
			mFadeInImage->setEnable(true);

			mBtnStart->setEnable(false);
			mBtnSetting->setEnable(false);
			mBtnExit->setEnable(false);
			mBtnGameMode->setEnable(false);
			mBtnEditMode->setEnable(false);
			mBtnCN->setEnable(false);
			mBtnEN->setEnable(false);
			mBtnShutDown->setEnable(false);
			mBtnReturn->setEnable(false);
			mBtnCancel->setEnable(false);
			break;
		case EditStart:
			mState = LoadingEdit;
			mFadeInImage->setEnable(true);

			mBtnStart->setEnable(false);
			mBtnSetting->setEnable(false);
			mBtnExit->setEnable(false);
			mBtnGameMode->setEnable(false);
			mBtnEditMode->setEnable(false);
			mBtnCN->setEnable(false);
			mBtnEN->setEnable(false);
			mBtnShutDown->setEnable(false);
			mBtnReturn->setEnable(false);
			mBtnCancel->setEnable(false);
			break;
		case CompanyTitle:
			if (mCompanyTitle->isEnd())
			{
				mState = TeamTitle;
				mTeamTitle->setEnable(true);
				mCompanyTitle->setEnable(false);
			}
			break;
		case TeamTitle:
			if (mTeamTitle->isEnd())
			{
				mState = Canvas;
				mCanvas->setEnable(true);
				mTeamTitle->setEnable(false);
				SoundManager::sGetInstance()->playAudio(4);
			}
			break;
		case Canvas:
			if (mCanvas->isEnd())
			{
				mState = MainMenu;
				mCanvas->setEnable(false);
			}
			mBtnStart->setEnable(true);
			mBtnSetting->setEnable(true);
			mBtnExit->setEnable(true);
			break;
		case Empty:
			break;
		case LoadingGame:
			if (mFadeInImage->isEnd() != true)
			{
				break;
			}
			return GameLevelManager::sGetInstance()->changeLevel(2);
		case LoadingEdit:
			if (mFadeInImage->isEnd() != true)
			{
				break;
			}
			return GameLevelManager::sGetInstance()->changeLevel(3);
		}

	SceneManager::sGetInstance()->onLateUpdate(deltaTime);
	return this;
}

void Level01::leaveLevel()
{
	Engine::sGetInstance()->enableGameMode(false);

	mBtnStart->destroy();
	mBtnSetting->destroy();
	mBtnExit->destroy();
	mBtnGameMode->destroy();
	mBtnEditMode->destroy();
	mBtnCN->destroy();
	mBtnEN->destroy();
	mBtnShutDown->destroy();
	mBtnReturn->destroy();
	mBtnCancel->destroy();
	mFadeInImage->destroy();
	mCompanyTitle->destroy();
	mTeamTitle->destroy();
	mCanvas->destroy();

	delete mStartEvent;
	delete mSettingEvent;
	delete mExitEvent;
	delete mGameModeEvent;
	delete mEditEvent;
	delete mCNEvent;
	delete mENEvent;
	delete mShutDownEvent;
	delete mReturnEvent;
	delete mCancelEvent;

	mExhibition->destroy();
	mCamFollower->destroy();
	mCamera->destroy();

	SoundManager::sGetInstance()->stop(4);

	SceneManager::sGetInstance()->removeParticleFromPool(mRain);

	delete mCurrentGameMode;
	
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

void Level01::loadResource()
{
	mExhibition = SceneManager::sGetInstance()->createCube();
	SceneManager::sGetInstance()->createModel(*mExhibition, "Tank\\TankBattery", L"Tank\\TankTex");
	SceneManager::sGetInstance()->createModel(*mExhibition, "Tank\\TankBody", L"Tank\\TankTex");
	SceneManager::sGetInstance()->createModel(*mExhibition, "Tank\\TankTrack_L", L"Tank\\TankTrack");
	SceneManager::sGetInstance()->createModel(*mExhibition, "Tank\\TankTrack_R", L"Tank\\TankTrack");
	mExhibition->getTransform()->setScale(0.1f,0.1f,0.1f);

	mCamFollower = SceneManager::sGetInstance()->createEmptyObject();
	mCamera = SceneManager::sGetInstance()->createEmptyObject();
	auto cam = new Camera(mCamera);
	Camera::MainCamera = cam;
	mCamera->addComponent(cam);
	mCamera->attach(*mCamFollower);
	mCamera->getTransform()->translate(Vector3::forward*-25.0f + Vector3::up * 10.0f);

	mIsLoadFin = true;
	mState = CompanyTitle;
}

void Level01::loadParticle()
{
	mRain = SceneManager::sGetInstance()->createParticleSystem(L"VFX/Raindrop_01",1000);
	mRain->setEmitter(ParticleSystem::Emitter::Box);
	mRain->setEmitRate(300);
	mRain->setLifeTime(1.0f);
	mRain->setMaxMinSpeed(18.0f, 20.0f);
	mRain->setVelocity(0.0f, -1.0f, 0.0f);
	Material mat;
	mat.Color = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.3f);
	mRain->setTile(1.0f, 1.0f);
	mRain->setMaterial(mat);
	mRain->enableLoop(true);
	mRain->setPosition(0.0f, 20.0f, 0.0f);
	mRain->setRange(3.0f, 1.0f, 3.0f);
	mRain->play();
}
