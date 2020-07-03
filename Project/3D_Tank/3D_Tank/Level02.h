#pragma once
#include "GameLevelBase.h"

class AirWall;

class Level02 : public GameLevelBase
{
public:
	Level02();
	~Level02();

	void enterLevel() override;
	GameLevelBase* onUpdate(float deltaTime) override;
	void leaveLevel() override;
	void loadResourcce() override;

private:
	GameObject* mMap;
	std::vector<AirWall*> airWalls;
	void wakeupAI(int ID);
};

