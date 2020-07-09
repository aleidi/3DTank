#pragma once
#include "GameLevelBase.h"

class AirWall;
class AITank;
class FadeInOut;
class Potion;
class Weightless;
class TrackTransform;

class Level02 : public GameLevelBase
{
public:
	Level02();
	~Level02();

	void enterLevel() override;
	GameLevelBase* onUpdate(float deltaTime) override;
	void leaveLevel() override;
	void loadResource() override;


private:
	enum State
	{
		Opening,
		Title,
		GameStart,
		Idel,
	};

private:
	void loadOpeningSequence();
	void loadEnvironment();
	void loadFirstWave();
	void loadSecondWave();
	void loadThirdWave();
	void loadBoss();

private:
	GameObject* mMap;
	std::vector<AirWall*> airWalls;
	std::vector<GameObject*> obstacles;
	std::vector<GameObject*> obstaclesPlay;
	std::vector<AITank*> firstWaveAI;
	std::vector<AITank*> secondWaveAI;
	std::vector<AITank*> thirdWaveAI;
	std::vector<Potion*> mItems;
	AITank* enemy_boss;
	Weightless* weightless;

	bool isWaveClear(std::vector<AITank*> thisWave);
	void wakeupAI(int ID);
	void wakeupWave(std::vector<AITank*> thisWave);
	void destroyWave(std::vector<AITank*> thisWave);

	bool secondloaded;
	bool thirdloaded;
	bool mIsInitLoad;
	bool mIsBossLoad;
	bool mIsEnvironmentLoad;

	float count = 0.0f;
	State mState;

	FadeInOut* mTitle;
	FadeInOut* mBackGround;
	TrackTransform* mOpening;
	GameObject* mCamera;

	float mTimer;
	bool mTrigger;
};

