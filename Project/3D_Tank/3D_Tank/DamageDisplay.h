#pragma once
#include "GameObject.h"

class UIText3D;
class Vector3;

class DamageDisplay : public GameObject
{
public:
	DamageDisplay();
	DamageDisplay(int value, const Vector3& start = Vector3::zero, float transition = 1.2f, float aliveTime = 1.45f, float upValue = 0.2f , float speed = 5.0f);

	void onLateUpdate(const float& deltaTime) override;
	void setSizeScale(float x, float y);
	void setStartPosition(const Vector3& pos);
	void setTransition(float value);
	void setAliveTime(float value);
	void setUpValue(float value);
	void setSpeed(float value);
	void setText(const std::wstring& text);
	void setEnable(bool value);
	bool isEnable();

private:
	UIText3D* mText;
	float mTransitionTime;
	float mAliveTime;
	float mTimeCount;
	float mSpeed;
	Vector3 mTargetPos;
	bool mIsEnable;

};

