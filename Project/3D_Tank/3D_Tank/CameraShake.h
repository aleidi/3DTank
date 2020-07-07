#pragma once

class PerlinNoise;
class Camera;

class CameraShake
{
public:
	static CameraShake* sGetInstance();
	static void createSingleton();

	void setDistance(float x, float y, float z);
	void setPerlinParam(float x = 3.0f, float y = 2.0f, float z = 6.2f);
	void setAmplitude(float x, float y, float z);
	void doShake(float deltaTime);

private:
	CameraShake();
	~CameraShake();

private:
	static CameraShake* sInstance;

	PerlinNoise* mNoise;
	float mDisX;
	float mDisY;
	float mDisZ;
	float mNoiseParamX;
	float mNoiseParamY;
	float mNoiseParamZ;
	float mAmplitudeX;
	float mAmplitudeY;
	float mAmplitudeZ;
	int mCount;
	float mNoiseValue;
	float mOffsetX;
	float mOffsetY;
	float mOffsetZ;
};

