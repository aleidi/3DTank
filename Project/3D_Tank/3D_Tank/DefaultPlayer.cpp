#include "DefaultPlayer.h"
#include "GameCommon.h"
#include "DefaultCameraCtrl.h"

DefaultPlayer::DefaultPlayer()
{

	mCamera = new Camera(this);
	this->addComponent(mCamera);
	mCamera->MainCamera = mCamera;
}

DefaultPlayer::~DefaultPlayer()
{
	delete mCamera;
	mCamera = nullptr;
}

void DefaultPlayer::MoveForward(float value)
{
	mTransform->translate(mTransform->Forward * value);
}

void DefaultPlayer::MoveRight(float value)
{
	mTransform->translate(mTransform->Right * value);
}

void DefaultPlayer::MoveUp(float value)
{
	mTransform->translate(mTransform->Up * value);
}

void DefaultPlayer::Rotate(float x, float y, float z)
{
	mTransform->rotateX(x);
	mTransform->rotateY(y);
	mTransform->rotateZ(z);
}

