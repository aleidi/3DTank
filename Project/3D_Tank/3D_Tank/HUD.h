#pragma once
#include "GameObject.h"

class UIImage;

class HUD : public GameObject
{
public:
	HUD();
	~HUD();

	void setAccelator(const float& inner, const float& outer);
	void onLateUpdate(const float& deltaTime) override;

	void enableShow(const bool& value);

private:
	UIImage* mCrossHairInner;
	UIImage* mCrossHairOuter;

	float mRotSpdInner;
	float mRotSpdOuter;
	float mAccelatorInner;
	float mAccelatorOuter;
};

