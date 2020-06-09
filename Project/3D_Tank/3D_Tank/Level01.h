#pragma once

#include "GameLevelBase.h"

class Level01 : public GameLevelBase
{
public :
	Level01();
	~Level01();

	void enterLevel() override;
	GameLevelBase* onUpdate(float deltaTime) override;
	void leaveLevel() override;
};

