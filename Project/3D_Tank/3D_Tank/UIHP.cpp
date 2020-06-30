#include "UIHP.h"
#include "UIImage3D.h"
#include "GameCommon.h"

UIHP::UIHP()
{
	mName = "UIHP";

	mFrame = SceneManager::sGetInstance()->createUIImage3D(L"UI/HpFrame");
	mFrame->setSize(0.42f, 0.057f);

	mImage = SceneManager::sGetInstance()->createUIImage3D(L"");
	Material mat;
	mat.Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	mImage->setMaterial(mat);
	mImage->setSize(0.4f, 0.05f);
}

UIHP::~UIHP()
{
	SceneManager::sGetInstance()->removeUI3DFromPool(mImage);
	SceneManager::sGetInstance()->removeUI3DFromPool(mFrame);
}

void UIHP::onLateUpdate(float deltaTime)
{
	Vector3 pos = mTransform->getPosition();
	mFrame->setPosition(pos.x, pos.y, pos.z);
	mImage->setPosition(pos.x, pos.y, pos.z);
}

void UIHP::setFillAmount(float value)
{
	mImage->setFillAmount(value);
}

void UIHP::setFillType(FillType type)
{
	mImage->setFillType(type);
}
