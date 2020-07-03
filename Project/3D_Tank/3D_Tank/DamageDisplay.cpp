#include <string>

#include "DamageDisplay.h"
#include "UIText3D.h"
#include "SceneManager.h"
#include "Math.h"
#include "Vector3.h"

DamageDisplay::DamageDisplay()
	:DamageDisplay(0,Vector3::zero,1.2f,1.45f,0.2f,5.0f)
{
}

DamageDisplay::DamageDisplay(int value, const Vector3 & start, float transition, float aliveTime, float upValue, float speed)
	: mTransitionTime(transition), mAliveTime(aliveTime),mTimeCount(0.0f),mSpeed(speed),mIsEnable(false)
{
	mText = SceneManager::sGetInstance()->createUIText3D(std::to_wstring(value));
	mText->setPosition(start.x, start.y, start.z);
	mTargetPos = start;
	mTargetPos.y += upValue;
	mText->setEnable(false);
}

void DamageDisplay::onLateUpdate(float deltaTime)
{
	if (!mIsEnable)
	{
		return;
	}

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
		//SceneManager::sGetInstance()->removeUI3DFromPool(mText);
		//destroy();
		mIsEnable = false;
		mText->setEnable(false);
		mTimeCount = 0.0f;
	}
}

void DamageDisplay::setSizeScale(float x, float y)
{
	mText->setSizeScale(x, y);
}

void DamageDisplay::setStartPosition(const Vector3 & pos)
{
	mTargetPos = pos;
	mText->setPosition(pos.x, pos.y, pos.z);
}

void DamageDisplay::setTransition(float value)
{
	mTransitionTime = value;
}

void DamageDisplay::setAliveTime(float value)
{
	mAliveTime = value;
}

void DamageDisplay::setUpValue(float value)
{
	mTargetPos.y += value;
}

void DamageDisplay::setSpeed(float value)
{
	mSpeed = value;
}

void DamageDisplay::setText(const std::wstring & text)
{
	mText->setText(text);
}

void DamageDisplay::setEnable(bool value)
{
	mIsEnable = value;
	mText->setEnable(value);
}

bool DamageDisplay::isEnable()
{
	return mIsEnable;
}
