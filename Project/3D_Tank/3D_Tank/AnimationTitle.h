#pragma once
#include "GameObject.h"

class UIImage;

class AnimationTitle : public GameObject
{
public:
	AnimationTitle(float posStartX, float posStartY, float animTime1, float animTime2, float stopTime,const std::wstring& image, Vector3 velocity);
	~AnimationTitle();

	void onLateUpdate(float deltaTime) override;
	void setImageSize(float width, float height);
	void setRotation(float pitch, float yaw, float roll, bool isDeg);
	bool isEnd();
	void setEnable(bool value);
	void setColor(DirectX::XMFLOAT4 color);

private:
	float mAnimTime1;
	float mAnimTime2;
	float mStopTime;
	bool mIsStop;
	bool mIsAnim1Fin;
	bool mIsEnd;
	bool mIsActive;
	float mAnimCount;
	float mStopCount;
	UIImage* mImage;
	Vector3 mVelocity;
};

