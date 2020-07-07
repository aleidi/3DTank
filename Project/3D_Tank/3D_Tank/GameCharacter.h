#pragma once
#include "Pawn.h"
#include "MovementComponent.h"

class GameCharacter : public Pawn
{
public:
	GameCharacter();
	virtual ~GameCharacter();

	virtual void onStart() override;
	virtual void onUpdate(const float& deltaTime) override;
	virtual void Move(Vector3 value);

	MovementComponent* getMoveComponent();

private:
	MovementComponent* movecomp;
};

