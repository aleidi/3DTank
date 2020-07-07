#pragma once
#include "GameObject.h"
#include "LightHelper.h"

class UIImage;

class FadeInOut : public GameObject
{
public:
	enum Type
	{
		FadeOut = 0,
		FadeIn = 1
	};
public:
	FadeInOut(const std::wstring& image, float width, float height, float posX, float posY, float fadeTime, Type type);
	~FadeInOut();
	
	void onLateUpdate(const float& deltaTime) override;
	void setEnable(bool value);
	bool isEnd();

private:
	float mStep;
	Type mType;

	UIImage* mImage;
	Material mMat;
	float mAmount;
	bool mIsEnd;
	bool mIsActivate;
};

