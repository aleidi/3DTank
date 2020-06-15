#pragma once
#include "ControllerBase.h"

class AIController : public ControllerBase
{
public:
	AIController();
	virtual ~AIController();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;

	virtual void MoveCharacter(Vector3 value);
};
