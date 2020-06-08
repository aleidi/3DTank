#pragma once
class GameInput
{
public:
	static GameInput* sGetInstance();
	static void creataSingleton();
	static void destroy();

	bool onInit();
	bool onUpdate(float deltaTime);
private:
	GameInput();
	~GameInput();

private:
	static GameInput* sInstance;
};

