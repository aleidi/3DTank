#pragma once
#include "GameObject.h"

class UIImage;

class HUD : public GameObject
{
public:
	HUD();
	~HUD();

	void setAccelator(float inner, float outer);
	void onLateUpdate(const float& deltaTime) override;

private:
	UIImage* mCrossHairInner;
	UIImage* mCrossHairOuter;

	float mRotSpdInner;
	float mRotSpdOuter;
	float mAccelatorInner;
	float mAccelatorOuter;
};

