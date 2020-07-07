#include "MagicBall.h"
#include "SceneManager.h"
#include "VFXSphere.h"
#include "Transform.h"

MagicBall::MagicBall()
	:mCanTile(false),mTileX(1.0f),mTileY(1.0f), mTarget(), mCanChase(false)
{
	mVFX = SceneManager::sGetInstance()->createVFXSphere();
}

MagicBall::~MagicBall()
{
	SceneManager::sGetInstance()->removeVFXSphereFromPool(mVFX);
}

void MagicBall::onUpdate(const float& deltaTime)
{
	if (mCanChase)
	{
		Vector3 dir = mTarget - mTransform->getPosition();
		dir.x *= deltaTime;
		dir.y *= deltaTime;
		dir.z *= deltaTime;

		mTransform->translate(dir.x, dir.y, dir.z);
	}

	if (!mCanTile)
	{
		return;
	}

	mVFX->tileOffset(mTileX*deltaTime, mTileY*deltaTime);

}

void MagicBall::onLateUpdate(const float & deltaTime)
{
	Vector3 pos = mTransform->getPosition();
	mVFX->setPosition(pos.x, pos.y, pos.z);
}

void MagicBall::enableTile(bool value)
{
	mCanTile = value;
}

void MagicBall::setColor(const DirectX::XMFLOAT4& color)
{
	Material mat;
	mat.Color = color;
	mVFX->setMaterial(mat);
}

void MagicBall::setTile(const float& x, const float& y)
{
	mTileX = x;
	mTileY = y;
}

void MagicBall::setTarget(const Vector3 & target)
{
	mTarget = target;
}

void MagicBall::enableChase(const bool & value)
{
	mCanChase = value;
}
