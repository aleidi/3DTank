#pragma once
#include "GameObject.h"

class UIText3D;
class Vector3;

class DamageDisplay : public GameObject
{
public:
	DamageDisplay() = delete;
	DamageDisplay(int value = 0, const Vector3& start = Vector3::zero, float transition = 1.2f, float aliveTime = 1.45f, float upValue = 0.2f , float speed = 5.0f);

	void onLateUpdate(float deltaTime) override;

private:
	UIText3D* mText;
	float mTransitionTime;
	float mAliveTime;
	float mTimeCount;
	float mSpeed;
	Vector3 mTargetPos;

};

