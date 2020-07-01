#pragma once
class GameSystem
{
public:
	GameSystem();
	~GameSystem();

	void onInit();
	void onUpdate(float deltaTime);
	
	void setEnable(bool value);
};

