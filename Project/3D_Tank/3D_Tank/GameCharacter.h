#pragma once
#include "Pawn.h"

class GameCharacter : public Pawn
{
public:
	GameCharacter();
	virtual ~GameCharacter();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void Move(Vector3 value);
};

