#include "DefaultPlayer.h"
#include "GameCommon.h"
#include "DefaultCameraCtrl.h"
#include "UIHP.h"

DefaultPlayer::DefaultPlayer()
{
	mName = "DefaultPlayer";

	mCamera = new Camera(this);
	this->addComponent(mCamera);
	Camera::MainCamera = mCamera;
	reinterpret_cast<UIHP*>(mUIHP)->setEnable(false);
}

DefaultPlayer::~DefaultPlayer()
{
}

void DefaultPlayer::destroy()
{
	SceneManager::sGetInstance()->removeGameObjectFromPool(this);
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

Camera * DefaultPlayer::GetCamera()
{
	return mCamera;
}

