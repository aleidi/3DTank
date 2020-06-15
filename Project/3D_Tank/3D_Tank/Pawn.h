#pragma once

#include "GameObject.h"

class MovementComponent;

class Pawn : public GameObject
{
public:
	Pawn();
	virtual ~Pawn();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;

protected:
	MovementComponent* mMovementComp;
};