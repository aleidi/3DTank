#include "AnimationTitle.h"
#include "UIImage.h"
#include "SceneManager.h"

AnimationTitle::AnimationTitle(float posStartX, float posStartY, float animTime1, float animTime2, float stopTime, const std::wstring & image, Vector3 velocity)
	:mIsStop(false), mIsAnim1Fin(false), mIsEnd(false), mIsActive(false), mAnimCount(0.0f), mStopCount(0.0f), mVelocity(velocity)
{
	mImage = SceneManager::sGetInstance()->createUIImage(image);
	mImage->setPosition(posStartX, posStartY);
	mAnimTime1 = animTime1;
	mAnimTime2 = animTime2;
	mStopTime = stopTime;
}

AnimationTitle::~AnimationTitle()
{
	SceneManager::sGetInstance()->removreUIFromPool(mImage);
}

void AnimationTitle::onLateUpdate(const float& deltaTime)
{
	if (mIsActive != true)
	{
		return;
	}

	if (mIsStop)
	{
		mStopCount += deltaTime;
		if (mStopCount >= mStopTime)
		{
			mIsStop = false;
		}
		return;
	}

	mAnimCount += deltaTime;
	if (mIsAnim1Fin != true && mAnimCount > mAnimTime1)
	{
		mIsAnim1Fin = true;
		mIsStop = true;
		mAnimCount = 0.0f;
		return;
	}


	if (mIsAnim1Fin != false && mAnimCount > mAnimTime2)
	{
		mIsEnd = true;
		return;
	}

	Vector3 pos;
	mImage->getPosition(pos.x, pos.y);
	pos = pos + mVelocity *deltaTime;
	mImage->setPosition(pos.x,pos.y);

}

void AnimationTitle::setImageSize(float width, float height)
{
	mImage->setSize(width, height);
}

void AnimationTitle::setRotation(float pitch, float yaw, float roll, bool isDeg)
{
	mImage->setRotation(pitch, yaw, roll, isDeg);
}

bool AnimationTitle::isEnd()
{
	return mIsEnd;
}

void AnimationTitle::setEnable(bool value)
{
	mIsActive = true;
}

void AnimationTitle::setColor(DirectX::XMFLOAT4 color)
{
	Material mat;
	mat.Color = color;
	mImage->setMaterial(mat);
}
