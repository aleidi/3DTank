#pragma once

class Pawn;
class ControllerBase;

class GameInstance
{
public:
	static GameInstance* sGetInstance();
	static void createSingleton();
	static void Destroy();

	bool onInit();
	bool onUpdate(float deltaTime);

	Pawn* getPlayer();
	ControllerBase* getPlayerController();

private:
	GameInstance();
	~GameInstance();

private:
	static GameInstance* sInstance;
};

