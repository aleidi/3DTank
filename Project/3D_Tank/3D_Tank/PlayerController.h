#pragma once
#include "ControllerBase.h"

class PlayerController : public ControllerBase
{
public:
	PlayerController();
	~PlayerController();

	virtual void onUpdate(float deltaTime) override;
private:
	void Move(Vector3 value);
	void Rotate(float valueX, float valueY);
	void Attack1();
	void Skill1();

	void checkInput(float deltaTime);
};

