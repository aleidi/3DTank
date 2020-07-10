#include <thread>

#include "Level02.h"
#include "AITank.h"
#include "PlayerTank.h"
#include "EnemyBoss.h"
#include "AIController.h"
#include "GameModeTP.h"
#include "RenderManager.h"
#include "GameInstance.h"
#include "PlayerController.h"
#include "EntityNames.h"
#include "Transform.h"
#include "GameCharacter.h"
#include "MessageDispatcher.h"
#include "AirWall.h"
#include "SM_construction_fence.h"
#include "SM_WaterTank.h"
#include "SM_Crate.h"
#include "FreightContainer_A.h"
#include "ShellContainer.h"
#include "Potion.h"
#include "FadeInOut.h"
#include "Weightless.h"
#include "FileManager.h"
#include "TrackTransform.h"

//std::wstring wstr;
//float x = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition().x;
//float y = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition().y;
//float z = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition().z;
//wstr += std::to_wstring(x) + L"," + std::to_wstring(y) + L"," + std::to_wstring(z);
//Engine::sGetInstance()->showtText(wstr.c_str(), 0, 0, 300, 300, true);

Level02::Level02()
	:mTimer(0.0f), mIsInitLoad(false),mIsBossLoad(false), secondloaded(false), thirdloaded(false),
	 mIsEnvironmentLoad(false),mTrigger(false)
{
	GameLevelManager::sGetInstance()->addLevel(2, this);
}

Level02::~Level02()
{
}

void Level02::enterLevel()
{
	SceneManager::sGetInstance()->setSkyBox(L"Skybox/Sand");

	//load opening sequence
	loadOpeningSequence();

	mTitle = new FadeInOut(L"UI/Title1", WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f, 2.0f, FadeInOut::Type::FadeOut);
	mBackGround = new FadeInOut(L"UI/FadeBlack", WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f, 4.0f, FadeInOut::Type::FadeOut);

	std::thread t(&Level02::loadResource, this);
	t.detach();

	std::thread t2(&Level02::loadBoss, this);
	t2.detach();

	std::thread t3(&Level02::loadFirstWave, this);
	t3.detach();

	std::thread t4(&Level02::loadEnvironment, this);
	t4.detach();

	mState = Title;
	mCanStart = true;

	Engine::sGetInstance()->enableGameMode(true);
}

GameLevelBase * Level02::onUpdate(float deltaTime)
{
	if (!mCanStart)
	{
		return this;
	}


	SceneManager::sGetInstance()->onUpdate(deltaTime);

	switch (mState)
	{
	case Level02::Title:
		mTimer += deltaTime;
		if (mTimer > 5.0f)
		{
			mBackGround->setEnable(true);
		}
		if (mBackGround->isEnd())
		{
			mTitle->setEnable(true);
			mState = Level02::Opening;
			SoundManager::sGetInstance()->playLoopAudio(1);
		}
		return this;

	case Level02::Opening:
		if (!mTitle->isEnd())
		{
			return this;
		}
		if (Camera::MainCamera != mCamera->getComponent<Camera>())
		{
			Camera::MainCamera = mCamera->getComponent<Camera>();
		}
		mOpening->play(deltaTime);
		if (mOpening->isFin())
		{
			mState = GameStart;
		}
		break;
	case Level02::GameStart:
			Camera::MainCamera = reinterpret_cast<PlayerTank*>(GameInstance::sGetInstance()->getPlayer())->getCamera();
			GameInstance::sGetInstance()->getPlayerController()->setEnable(true);
			reinterpret_cast<PlayerTank*>(GameInstance::sGetInstance()->getPlayer())->enableHUD(true);
			wakeupWave(firstWaveAI);
			mState = FirstWave;
			break;
	case Level02::FirstWave:
		if (!secondloaded && isWaveClear(firstWaveAI)) {

			count += deltaTime;
			if (count >= 12.0f) {
				count = 0.0f;
				destroyWave(firstWaveAI);
				loadSecondWave();
				wakeupWave(secondWaveAI);
				secondloaded = true;
				mState = SecondWave;
			}
		}
		break;
	case Level02::SecondWave:
		if (!thirdloaded && secondloaded && isWaveClear(secondWaveAI)) {

			count += deltaTime;
			if (count >= 12.0f) {
				count = 0.0f;
				destroyWave(secondWaveAI);
				loadThirdWave();
				wakeupWave(thirdWaveAI);
				thirdloaded = true;
				mState = Idel;
			}
		}
		break;
	case Level02::Idel:
		break;
	}

	if (!mIsInitLoad || !mIsBossLoad)
	{
		return this;
	}
	
//	std::wstring wstr;
//float x = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition().x;
//float y = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition().y;
//float z = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition().z;
//wstr += std::to_wstring(x) + L"," + std::to_wstring(y) + L"," + std::to_wstring(z);
//Engine::sGetInstance()->showtText(wstr.c_str(), 0, 0, 300, 300, true);
	RenderManager::sGetInstance()->rotateLight(0.0f, deltaTime*10.0f, 0.0f);

	Dispatch->DispatchDelayedMessages();

	SceneManager::sGetInstance()->onLateUpdate(deltaTime);

	return this;
}

void Level02::leaveLevel()
{
	Engine::sGetInstance()->enableGameMode(false);

	mTitle->destroy();
	mBackGround->destroy();
}

void Level02::loadResource()
{
	mMap = SceneManager::sGetInstance()->createEmptyObject();
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m0_wall3", L"Objects/Level/wall3");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m1_wall2", L"Objects/Level/wall2");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m2_wall5", L"Objects/Level/wall5");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m3_c2", L"Objects/Level/c2");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m4_c1", L"Objects/Level/c1");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m5_cn", L"Objects/Level/cn");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m6_P1", L"Objects/Level/P1");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m7_c4", L"Objects/Level/c4");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m8_arc1", L"Objects/Level/arc1");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m9_arc2", L"Objects/Level/arc2");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m10_arc3", L"Objects/Level/arc3");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m11_tree", L"Objects/Level/tree");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m12_reaf", L"Objects/Level/reaf");
	mMap->getTransform()->translate(0.0f, -0.075f, 0.0f);
	mMap->getTransform()->setScale(0.07f, 0.07f, 0.07f);

	ShellContainer::onInit();

	mIsInitLoad = true;
}

void Level02::wakeupAI(int ID) {
	if (SceneManager::sGetInstance()->getAIController(ID) != nullptr ) 
		SceneManager::sGetInstance()->getAIController(ID)->wakeup();

}

void Level02::loadOpeningSequence()
{
	mCamera = SceneManager::sGetInstance()->createEmptyObject();
	mCamera->addComponent(new Camera(mCamera));
	mCamera->getTransform()->setPosition(Vector3(28.4502f, 9.65098f, 20.4881f));
	mCamera->getTransform()->setRotation(Vector3(0.596903f, 3.35801f, 0.0f));
	Camera::MainCamera = mCamera->getComponent<Camera>();
	Camera::MainCamera->Position = mCamera->getTransform()->getPosition();
	Camera::MainCamera->Rotation = mCamera->getTransform()->getRotation();

	FileManager::LoadKeyFrames("Sequence");

	mOpening = new TrackTransform(mCamera->getTransform());
	TrackTransform::Frame f;
	for (int i = 0; i < FileManager::KeyFrames.size(); ++i)
	{
		for (int j = 0; j < FileManager::KeyFrames[i].size(); ++j)
		{
			f.Key = FileManager::KeyFrames[i][j].Key;
			f.KeyData.Position = FileManager::KeyFrames[i][j].Position;
			f.KeyData.Rotation = FileManager::KeyFrames[i][j].Rotation;
			f.KeyData.Scale = FileManager::KeyFrames[i][j].Scale;
			mOpening->addKeyFrame(f);
		}
	}
}

void Level02::loadEnvironment()
{
	//// seven buildings'

	Vector3 position, scale;
	position = Vector3(-16.5, 7, 12.5);
	scale = Vector3(21.5, 14, 16);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(-17, 7, -14.3);
	scale = Vector3(22, 14, 22.5);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(17, 6.8, -4.3);
	scale = Vector3(15.2, 13.7, 44.4);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(-16.5, 6.5, -40.6);
	scale = Vector3(21.2, 15, 15.3);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(17.4, 4.9, -40.6);
	scale = Vector3(15.3, 9.8, 14.2);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(-16.8, 7, -66.7);
	scale = Vector3(21.6, 14, 22.2);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(17.4, 6.5, -65.8);
	scale = Vector3(15.3, 13, 21.1);
	airWalls.push_back(new AirWall(position, scale));

	// four walls'
	position = Vector3(-1, 4.5, 32.2);
	scale = Vector3(75, 9, 0.05);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(-1, 4.5, -87.2);
	scale = Vector3(75, 9, 0.05);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(-37.8, 5.5, -28);
	scale = Vector3(0.05, 11.3, 120);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(36.3, 5, -28);
	scale = Vector3(0.05, 10.3, 120);
	airWalls.push_back(new AirWall(position, scale));

	// ground's
	position = Vector3(-0.8, -0.57, -27.4);
	scale = Vector3(77.2, 1, 120);
	airWalls.push_back(new AirWall(position, scale));

	// obstacles fence
	position = Vector3(-38, -0.5, 33);
	scale = Vector3(0.05, 0.01, 0.01);
	Vector3 rotation = Vector3(0, -3.1425926 / 2.0, 0); // PI / 2
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, 18);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, 3);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, -12);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, -27);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, -42);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, -57);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, -72);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-16, -0.5, 32.2);
	scale = Vector3(0.075, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-16, -0.5, -87);
	scale = Vector3(0.075, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-12.8, -0.5, 18.5);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-13, -0.5, 5.5);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-26.5, -0.5, 18.5);
	scale = Vector3(0.043, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-13.3, -0.5, -3.5);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-13.3, -0.5, -25);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-27, -0.5, -3.6);
	scale = Vector3(0.07, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-12.8, -0.5, -34.5);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-13, -0.5, -47.5);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-26.5, -0.5, -34.5);
	scale = Vector3(0.043, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-13.3, -0.5, -56);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-13.3, -0.5, -77.4);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-27, -0.5, -56);
	scale = Vector3(0.07, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));
	/////////////////////////////////////
	/*position = Vector3(1.0, 0, -26.0);
	scale = Vector3(0.02, 0.01, 0.03);
	rotation = Vector3(0, -3.1425926, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-6.0, 0, -19.0);
	scale = Vector3(0.02, 0.01, 0.03);
	rotation = Vector3(0, -3.1425926, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));*/

	// obstacles FreightContainer
	position = Vector3(-19, 0, -50);
	scale = Vector3(0.03, 0.005, 0.005);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new FreightContainer_A(position, rotation, scale, 1));

	position = Vector3(30.5, 0, -4.0);
	scale = Vector3(0.018, 0.018, 0.018);
	rotation = Vector3(0, 25.0, 0);
	obstaclesPlay.push_back(new FreightContainer_A(position, rotation, scale, 1));

	position = Vector3(4, 0, -84);
	scale = Vector3(0.01, 0.01, 0.01);
	rotation = Vector3(0, 70, 0);
	obstaclesPlay.push_back(new FreightContainer_A(position, rotation, scale, 1));

	position = Vector3(4, 2.5, -84);
	scale = Vector3(0.01, 0.01, 0.01);
	rotation = Vector3(0, 85, 0);
	obstaclesPlay.push_back(new FreightContainer_A(position, rotation, scale, 1));

	// obstacles WaterTank
	position = Vector3(2.5, 0, -23.0);
	scale = Vector3(0.06, 0.02, 0.02);
	rotation = Vector3(-3.1415926 / 2.0, 0.2, 0);
	obstaclesPlay.push_back(new SM_WaterTank(position, rotation, scale));

	position = Vector3(-5.2, 0, -20.0);
	scale = Vector3(0.06, 0.02, 0.02);
	rotation = Vector3(0, -0.4, 0);
	obstaclesPlay.push_back(new SM_WaterTank(position, rotation, scale));

	position = Vector3(-5.2, 0, -20.0);
	scale = Vector3(0.06, 0.02, 0.02);
	rotation = Vector3(0, -0.4, 0);
	obstaclesPlay.push_back(new SM_WaterTank(position, rotation, scale));

	// Crate
	position = Vector3(-33, 0, -27.5);
	scale = Vector3(0.02, 0.015, 0.015);
	rotation = Vector3(0, 0, 0);
	obstaclesPlay.push_back(new SM_Crate(position, rotation, scale));

	position = Vector3(-35, 0, -26);
	scale = Vector3(0.02, 0.015, 0.015);
	rotation = Vector3(0, 0, 0);
	obstaclesPlay.push_back(new SM_Crate(position, rotation, scale));

	position = Vector3(0, 0.72, -40);
	scale = Vector3(0.02, 0.015, 0.015);
	rotation = Vector3(3.1415926 / 2.0, 0.3, 0);
	obstaclesPlay.push_back(new SM_Crate(position, rotation, scale));

	position = Vector3(-5, 0, -40);
	scale = Vector3(0.02, 0.015, 0.015);
	rotation = Vector3(0, 0.1, 0);
	obstaclesPlay.push_back(new SM_Crate(position, rotation, scale));

	position = Vector3(14.1, 0, 15.9);
	scale = Vector3(0.01, 0.01, 0.01);
	rotation = Vector3(0, -0.4, 0);
	obstaclesPlay.push_back(new FreightContainer_A(position, rotation, scale, 1));

	position = Vector3(12, 0, 17);
	scale = Vector3(0.015, 0.013, 0.015);
	rotation = Vector3(0, -0.3, 0);
	obstaclesPlay.push_back(new SM_Crate(position, rotation, scale));

	weightless = new Weightless();
	weightless->empty->getTransform()->setPosition(Vector3(1.43, 0, -29.83));

	position = Vector3(-5, 7, 0);
	scale = Vector3(0.015, 0.015, 0.015);
	rotation = Vector3(1.2, 0.7, 0.4);
	GameObject* floatObj = new SM_Crate(position, rotation, scale);
	floatObj->attach(*(weightless->empty));
	obstaclesPlay.push_back(floatObj);

	position = Vector3(4, 9, 5);
	scale = Vector3(0.015, 0.015, 0.015);
	rotation = Vector3(0.4, 1.5, 1.4);
	floatObj = new SM_Crate(position, rotation, scale);
	floatObj->attach(*(weightless->empty));
	obstaclesPlay.push_back(floatObj);

	position = Vector3(1.5, 11, -3);
	scale = Vector3(0.006, 0.006, 0.006);
	rotation = Vector3(0.8, 1.1, 2.1);
	floatObj = new FreightContainer_A(position, rotation, scale, 0);
	floatObj->attach(*(weightless->empty));
	obstaclesPlay.push_back(floatObj);

	mIsEnvironmentLoad = true;
}

void Level02::loadFirstWave() {
	mCurrentGameMode = new GameModeTP();
	reinterpret_cast<PlayerTank*>(GameInstance::sGetInstance()->getPlayer())->translate(30.0, 0, 9.0);
	//Camera::MainCamera = nullptr;
	GameInstance::sGetInstance()->getPlayerController()->setEnable(false);

	//potion
	Vector3 position;
	position = Vector3(30.0, 0.0, 2.0);
	auto item = new Potion();
	item->getTransform()->setPosition(position);
	mItems.push_back(item);

	position = Vector3(-36, 0, -28);
	item = new Potion();
	item->getTransform()->setPosition(position);
	mItems.push_back(item);

	position = Vector3(-4, 0, -22);
	item = new Potion();
	item->getTransform()->setPosition(position);
	mItems.push_back(item);

	position = Vector3(-5, 0, -79);
	item = new Potion();
	item->getTransform()->setPosition(position);
	mItems.push_back(item);

	firstWaveAI.push_back(new AITank(ent_Tank_Enemy01)); //ok
	firstWaveAI.push_back(new AITank(ent_Tank_Enemy02)); //ok
	firstWaveAI.push_back(new AITank(ent_Tank_Enemy03)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy04)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy05)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy06)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy07)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy08)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy09)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy10)); //ok	
}

void Level02::loadSecondWave() {
	secondWaveAI.push_back(new AITank(ent_Tank_Enemy04));
	secondWaveAI.push_back(new AITank(ent_Tank_Enemy05));
	secondWaveAI.push_back(new AITank(ent_Tank_Enemy06));
	secondWaveAI.push_back(new AITank(ent_Tank_Enemy07));
}

void Level02::loadThirdWave() {
	//thirdWaveAI.push_back(new AITank(ent_Tank_Enemy08));
	//thirdWaveAI.push_back(new AITank(ent_Tank_Enemy09));
	//thirdWaveAI.push_back(new AITank(ent_Tank_Enemy10));

	weightless = new Weightless();
	weightless->empty->getTransform()->setPosition(Vector3(2, 0, -42));
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;
	position = Vector3(-5, 7, 0);
	scale = Vector3(0.015, 0.015, 0.015);
	rotation = Vector3(1.2, 0.7, 0.4);
	GameObject* floatObj = new SM_Crate(position, rotation, scale);
	floatObj->attach(*(weightless->empty));
	obstaclesPlay.push_back(floatObj);

	position = Vector3(4, 9, 5);
	scale = Vector3(0.015, 0.015, 0.015);
	rotation = Vector3(0.4, 1.5, 1.4);
	floatObj = new SM_Crate(position, rotation, scale);
	floatObj->attach(*(weightless->empty));
	obstaclesPlay.push_back(floatObj);

	position = Vector3(1.5, 11, -3);
	scale = Vector3(0.006, 0.006, 0.006);
	rotation = Vector3(0.8, 1.1, 2.1);
	floatObj = new FreightContainer_A(position, rotation, scale, 0);
	floatObj->attach(*(weightless->empty));
	obstaclesPlay.push_back(floatObj);

	enemy_boss->getCtrl()->wakeup();
	reinterpret_cast<EnemyBoss*>(enemy_boss->getTank())->showUI(true);

	SoundManager::sGetInstance()->playLoopAudio(2);
}

void Level02::loadBoss()
{
	enemy_boss = new AITank(ent_Tank_SuperEnemy);
	thirdWaveAI.push_back(enemy_boss);
	//reinterpret_cast<EnemyBoss*>(enemy_boss->getTank())->showUI(true);
	//enemy_boss->getCtrl()->wakeup();
	//enemy_boss->getCtrl()->wakeup();

	mIsBossLoad = true;
}

bool Level02::isWaveClear(std::vector<AITank*> thisWave) {
	for (int i = 0; i < thisWave.size(); ++i) {
		if (thisWave[i]->isAlive())
			return false;
	}

	return true;
}

void Level02::wakeupWave(std::vector<AITank*> thisWave) {
	for (int i = 0; i < thisWave.size(); ++i) {
		wakeupAI(thisWave[i]->getID());
	}

}

void Level02::destroyWave(std::vector<AITank*> thisWave) {
	for (int i = 0; i < thisWave.size(); ++i) {
		thisWave[i]->destroy();
	}
}