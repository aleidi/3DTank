#pragma once
#include "GameCharacter.h"

class MovementTest : public GameCharacter
{
	MovementTest();
	~MovementTest();

	void Move(Vector3 value) override;
};