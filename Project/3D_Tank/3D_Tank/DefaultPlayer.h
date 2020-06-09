#pragma once

#include "Pawn.h"

class DefaultPlayer : public Pawn
{
public:
	DefaultPlayer();
	~DefaultPlayer();

	void MoveForward(float value);
	void MoveRight(float value);
	void MoveUp(float value);
	void RotateCamera(float x, float y, float z);
	
private:
	GameObject* mCamFollow;
	GameObject* mCamera;
};