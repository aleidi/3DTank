#pragma once
#include "GameLevelBase.h"

class AirWall;
class AITank;

class Level02 : public GameLevelBase
{
public:
	Level02();
	~Level02();

	void enterLevel() override;
	GameLevelBase* onUpdate(float deltaTime) override;
	void leaveLevel() override;
	void loadResourcce() override;

	void loadFirstWave();
	void loadSecondWave();
	void loadThirdWave();

private:
	GameObject* mMap;
	std::vector<AirWall*> airWalls;
	std::vector<GameObject*> obstacles;
	std::vector<AITank*> firstWaveAI;
	std::vector<AITank*> secondWaveAI;
	std::vector<AITank*> thirdWaveAI;
	bool isWaveClear(std::vector<AITank*> thisWave);
	void wakeupAI(int ID);
	void wakeupWave(std::vector<AITank*> thisWave);
	bool secondloaded = false;
	bool thirdloaded = false;
};

