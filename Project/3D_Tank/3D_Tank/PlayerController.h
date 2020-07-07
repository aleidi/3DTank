#pragma once
#include "ControllerBase.h"

class PlayerController : public ControllerBase
{
public:
	PlayerController();
	~PlayerController();

	virtual void onUpdate(const float& deltaTime) override;
private:
	void move(Vector3 value);
	void rotate(float value);
	void rotateView(float valueX, float valueY);
	void adjustDistanceToCam(float value);
	void setCameraFov(float value);
	
	void checkInput(float deltaTime);

private:
	float mDisToCamFactor;
	float mMirrorMax;
	float mMirrorMin;
};

