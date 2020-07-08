#include "FadeInOut.h"
#include "UIImage.h"
#include "SceneManager.h"
#include "Math.h"

FadeInOut::FadeInOut(const std::wstring & image, float width, float height, float posX, float posY, float fadeTime, Type type)
	:mStep(1.0f/fadeTime),mType(type),mIsEnd(false), mIsActivate(false)
{
	mImage = SceneManager::sGetInstance()->createUIImage(image);
	mImage->setPosition(posX, posY);
	mImage->setSize(width, height);

	switch (mType)
	{
	case FadeInOut::FadeOut:
		mAmount = 1.0f;
		break;
	case FadeInOut::FadeIn:
		mAmount = 0.0f;
		break;
	}
	mMat = mImage->getMaterial();
	mMat.Color.w = mAmount;
	mImage->setMaterial(mMat);
}

FadeInOut::~FadeInOut()
{
	SceneManager::sGetInstance()->removreUIFromPool(mImage);
}

void FadeInOut::onLateUpdate(const float& deltaTime)
{
	if (mIsActivate != true || mIsEnd == true)
	{
		return;
	}

	switch (mType)
	{
	case FadeInOut::FadeOut:
		mAmount = Math::lerp(mAmount, 0.0f, mStep*deltaTime);
		if (mAmount < 0.05f)
		{
			mAmount = 0.0f;
			mIsEnd = true;
		}
		break;
	case FadeInOut::FadeIn:
		mAmount = Math::lerp(mAmount, 1.0f, mStep*deltaTime);
		if (mAmount > 0.95f)
		{
			mAmount = 1.0f;
			mIsEnd = true;
		}
		break;
	}
	mMat.Color.w = mAmount;
	mImage->setMaterial(mMat);
}

void FadeInOut::setEnable(bool value)
{
	mIsActivate = value;
}

bool FadeInOut::isEnd()
{
	return mIsEnd;
}
