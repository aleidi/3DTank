#pragma once
#include "GameLevelBase.h"
class GameLevelTest : public GameLevelBase
{
public:
	GameLevelTest();
	~GameLevelTest();

	void enterLevel() override;
	GameLevelBase* onUpdate(float deltaTime) override;
	void leaveLevel() override;

private:

};

