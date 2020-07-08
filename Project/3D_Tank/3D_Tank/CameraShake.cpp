#include <assert.h>
#include <math.h>

#include "CameraShake.h"
#include "PerlinNoise.h"
#include "Camera.h"
#include "Engine.h"

CameraShake* CameraShake::sInstance = nullptr;

CameraShake * CameraShake::sGetInstance()
{
	return sInstance;
}

void CameraShake::createSingleton()
{
	assert(!sInstance);
	sInstance = new CameraShake();
}

void CameraShake::setDistance(const float& x, const float& y, const float& z)
{
	mDisX = x;
	mDisY = y;
	mDisZ = z;
}

void CameraShake::setPerlinParam(const float& x, const float& y, const float& z)
{
	mNoiseParamX = x;
	mNoiseParamY = y;
	mNoiseParamZ = z;
}

void CameraShake::setAmplitude(const float& x, const float& y, const float& z)
{
	mAmplitudeX = x;
	mAmplitudeY = y;
	mAmplitudeZ = z;
}

void CameraShake::doShake(const float&  deltaTime)
{
	++mCount;
	mCount %= 2;
	if (mCount)
	{
		mNoiseValue = mNoise->noise(mNoiseParamX, mNoiseParamY, mNoiseParamZ);
		mOffsetX = mAmplitudeX * mDisX * mNoiseValue;
		mOffsetY = mAmplitudeY * mDisY * mNoiseValue;
		mOffsetZ = mAmplitudeZ * mDisZ * mNoiseValue;
	}
	else
	{
		mOffsetX = -mOffsetX;
		mOffsetY = -mOffsetY;
		mOffsetZ = -mOffsetZ;
	}
	Camera::MainCamera->Rotation.x += mOffsetX;
	Camera::MainCamera->Rotation.y += mOffsetY;
	Camera::MainCamera->Rotation.z += mOffsetZ;
}

CameraShake::CameraShake()
	:mDisX(0.0f),mDisY(0.0f),mDisZ(0.0f),mNoiseParamX(3.0f),mNoiseParamY(2.0f),mNoiseParamZ(6.2f),
	mAmplitudeX(1.0f), mAmplitudeY(1.0f),mAmplitudeZ(1.0f),mCount(0),mNoiseValue(0.0f),mOffsetX(0.0f),mOffsetY(0.0f),mOffsetZ(0.0f)
{
	mNoise = new PerlinNoise();
}

CameraShake::~CameraShake()
{
	delete mNoise;
}
