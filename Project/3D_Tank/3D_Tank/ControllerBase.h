#pragma once

#include "GameObject.h"

class Pawn;

class ControllerBase : public GameObject
{
public:
	ControllerBase() = default;
	ControllerBase(int value);
	virtual ~ControllerBase() {} 

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;

	void posses(Pawn* pawn) noexcept;
	void unPosses() noexcept;
	Pawn* getPawn() noexcept;
	void setEnable(bool value);

protected:
	Pawn* mPawn;

	bool mIsEnable;
};

