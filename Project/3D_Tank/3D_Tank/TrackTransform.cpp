#include "TrackTransform.h"
#include "Math.h"
#include "Transform.h"

#include "Engine.h"

TrackTransform::TrackTransform(Transform * target)
	:mTarget(target)
{
	Frame f;
	f.Key = 0.0f;
	f.KeyData.Position = mTarget->getPosition();
	f.KeyData.Rotation = mTarget->getRotation();
	f.KeyData.Scale = mTarget->getScale();
	addKeyFrame(f);
	mCurrentKey = 0;
	mCurrentTime = 0.0f;
	mIsActivate = false;
}

TrackTransform::~TrackTransform()
{
}

void TrackTransform::play(const float & deltaTime)
{
	if (!mIsActivate)
	{
		mTarget->setPosition(mKeyFrames[0].KeyData.Position);
		mTarget->setRotation(mKeyFrames[0].KeyData.Rotation);
		mTarget->setScale(mKeyFrames[0].KeyData.Scale);
		mIsActivate = true;
	}

	if (mCurrentKey > mKeyFrames.size() - 2)
	{
		Engine::sGetInstance()->showtText(L"fin", 0, 0, 500, 500, true);
		return;
	}

	mCurrentTime += deltaTime;

	Vector3 src = mTarget->getPosition();
	Vector3 dest = mKeyFrames[mCurrentKey + 1].KeyData.Position;
	float t = mKeyFrames[mCurrentKey + 1].Key - mKeyFrames[mCurrentKey].Key;
	mTarget->setPosition(Math::lerp(src, dest, deltaTime / t));

	src = mTarget->getRotation();
	dest = mKeyFrames[mCurrentKey + 1].KeyData.Rotation;
	mTarget->setRotation(Math::lerp(src, dest, deltaTime / t));

	src = mTarget->getScale();
	dest = mKeyFrames[mCurrentKey + 1].KeyData.Scale;
	mTarget->setScale(Math::lerp(src, dest, deltaTime / t));

	if (mCurrentTime > mKeyFrames[mCurrentKey+1].Key)
	{
		++mCurrentKey;
	}

}
