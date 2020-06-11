#pragma once

#include "GameObject.h"

class Pawn : public GameObject
{
public:
	Pawn() = default;
	virtual ~Pawn();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
};