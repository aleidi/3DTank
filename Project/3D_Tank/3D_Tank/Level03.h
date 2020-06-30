#pragma once
#include "GameLevelBase.h"

class Level03 : public GameLevelBase
{
public:
	Level03();
	~Level03();

	void enterLevel() override;
	GameLevelBase* onUpdate(float deltaTime) override;
	void leaveLevel() override;

private:
	GameObject* mMap;
};