#include <string>

#include "DamageDisplay.h"
#include "UIText3D.h"
#include "SceneManager.h"
#include "Math.h"
#include "Vector3.h"

DamageDisplay::DamageDisplay(int value, const Vector3 & start, float transition, float aliveTime, float upValue, float speed)
	: mTransitionTime(transition), mAliveTime(aliveTime),mTimeCount(0.0f),mSpeed(speed)
{
	mText = SceneManager::sGetInstance()->createUIText3D(std::to_wstring(value));
	mText->setPosition(start.x, start.y, start.z);
	mText->getPosition(mTargetPos.x, mTargetPos.y, mTargetPos.z);
	mTargetPos.y += upValue;
}

void DamageDisplay::onLateUpdate(float deltaTime)
{
	mTimeCount += deltaTime;
	if (mTimeCount < mTransitionTime)
	{
		Vector3 pos;
		mText->getPosition(pos.x, pos.y, pos.z);
		pos = Math::lerp(pos, mTargetPos, deltaTime*mSpeed*(1.0f/(mTransitionTime*mTransitionTime)));
		mText->setPosition(pos.x, pos.y, pos.z);
	}
	if (mTimeCount > mAliveTime)
	{
		SceneManager::sGetInstance()->removeUI3DFromPool(mText);
		destroy();
	}
}
