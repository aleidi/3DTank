#pragma once

#include "GameObject.h"

class Pawn;

class ControllerBase : public GameObject
{
public:
	ControllerBase() = default;
	virtual ~ControllerBase() {} 

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;

	void posses(Pawn* pawn) noexcept;
	void unPosses() noexcept;

	Pawn* getPawn() noexcept;

protected:
	Pawn* mPawn;
};
