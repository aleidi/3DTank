#pragma once

#include "ControllerBase.h"

class DefaultPlayerController : public ControllerBase
{
public:
	DefaultPlayerController();
	~DefaultPlayerController();

	void onStart() override;
	void onUpdate(float deltaTime) override;

private:
	float mRspdX;
	float mRspdY;
	float mMovSpd;
};
