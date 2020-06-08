#pragma once
class GameInstance
{
public:
	static GameInstance* sGetInstance();
	static void createSingleton();
	static void Destroy();

	bool onInit();
	bool onUpdate(float deltaTime);
private:
	GameInstance();
	~GameInstance();

private:
	static GameInstance* sInstance;
};

