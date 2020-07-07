#pragma once

#include "ControllerBase.h"

class DefaultPlayerController : public ControllerBase
{
public:
	DefaultPlayerController();
	~DefaultPlayerController();

	void onStart() override;
	void onUpdate(const float& deltaTime) override;

private:
	float mRspdX;
	float mRspdY;
	float mMovSpd;
};
