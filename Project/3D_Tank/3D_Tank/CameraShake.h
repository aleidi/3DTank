#pragma once

class PerlinNoise;
class Camera;

class CameraShake
{
public:
	static CameraShake* sGetInstance();
	static void createSingleton();

	void setDistance(const float& x, const float& y, const float& z);
	void setPerlinParam(const float& x = 3.0f, const float& y = 2.0f, const float& z = 6.2f);
	void setAmplitude(const float& x, const float& y, const float& z);
	void doShake(const float& deltaTime);

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

