#pragma once

#include "Pawn.h"

class Camera;

class DefaultPlayer : public Pawn
{
public:
	DefaultPlayer();
	~DefaultPlayer();

	void MoveForward(float value);
	void MoveRight(float value);
	void MoveUp(float value);
	void Rotate(float x, float y, float z);
	
private:
	Camera* mCamera;
};