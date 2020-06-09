#include "DefaultPlayer.h"
#include "GameCommon.h"
#include "CameraCtrl.h"

DefaultPlayer::DefaultPlayer()
{
	mCamFollow = SceneManager::sGetInstance()->createEmptyObject();
	mCamFollow->setName("follow");
	mCamFollow->attach(*this);
	mCamFollow->getTransform()->translate(0.0f, 0.0f, 0.0f);

	mCamera = SceneManager::sGetInstance()->createEmptyObject();
	mCamera->setName("camera");
	Camera* maincam = new Camera(mCamera);
	mCamera->addComponent(maincam);
	maincam->MainCamera = maincam;
	mCamera->addScriptComponent(new CameraCtrl(mCamera));
}

DefaultPlayer::~DefaultPlayer()
{
	delete mCamFollow;
	mCamFollow = nullptr;
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

void DefaultPlayer::RotateCamera(float x, float y, float z)
{
	mCamera->getTransform()->rotateX(x);
	mCamera->getTransform()->rotateY(y);
	mCamera->getTransform()->rotateZ(z);
}

