#pragma once
#include "GameLevelBase.h"

class Level02 : public GameLevelBase
{
public:
	Level02();
	~Level02();

	void enterLevel() override;
	GameLevelBase* onUpdate(float deltaTime) override;
	void leaveLevel() override;
};

