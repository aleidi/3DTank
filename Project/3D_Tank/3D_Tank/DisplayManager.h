#pragma once
#include <vector>

#include "Vector3.h"

class DamageDisplay;

class DisplayManager
{
public:
	static DisplayManager* sGetInstance();
	static void createSingleton();

	void displayText(const std::wstring& text, float sizeX, float sizeY, const Vector3 & start = Vector3::zero, float transition = 1.2f,
		float aliveTime = 1.45f, float upValue = 0.2f, float speed = 5.0f);
	void setTextAmount(int value);
	int getMaxText();

private:
	DisplayManager();
	~DisplayManager();

private:
	void createText();

private:
	static DisplayManager* sInstance;
	std::vector<DamageDisplay*> mTexts;

	int mMaxTexts;
	
};

