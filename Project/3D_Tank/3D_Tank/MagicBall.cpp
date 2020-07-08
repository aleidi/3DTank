#include "MagicBall.h"
#include "SceneManager.h"
#include "VFXSphere.h"
#include "Transform.h"
#include "Pawn.h"
#include "CameraShake.h"

MagicBall::MagicBall()
	:mCanTile(false),mTileX(1.0f),mTileY(1.0f), mTargetPos(), mCanChase(false),
	mTimer(0.0f), mAutoDestroyTime(4.0f), mSpeed(1.0f)
{
	mVFX = SceneManager::sGetInstance()->createVFXSphere();
}

MagicBall::~MagicBall()
{
	SceneManager::sGetInstance()->removeVFXSphereFromPool(mVFX);
}

void MagicBall::onUpdate(const float& deltaTime)
{
	mTimer += deltaTime;
	if (mTimer > mAutoDestroyTime)
	{
		destroy();
	}

	//detect whether hit targetpawn
	Vector3 dis{};
	if (mTargetPawn != nullptr)
	{
		dis = mTargetPawn->getTransform()->getPosition() - mTransform->getPosition();
		float length = Vector3::lengthSq(dis, Vector3::zero);
		if (length < 5.0f)
		{
			CameraShake::sGetInstance()->setDistance(dis.x, dis.y, dis.z);
			CameraShake::sGetInstance()->doShake(deltaTime);
		}
		if (length < 1.0f)
		{
			mTargetPawn->hited((float)rand() / (float)RAND_MAX * 100 + 100);
			destroy();
		}
	}

	//move to target position
	if (mCanChase)
	{
		dis = mTargetPos - mTransform->getPosition();
		dis.x *= deltaTime * mSpeed;
		dis.y *= deltaTime * mSpeed;
		dis.z *= deltaTime * mSpeed;

		mTransform->translate(dis.x, dis.y, dis.z);
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
	mTargetPos = target;
}

void MagicBall::enableChase(const bool & value)
{
	mCanChase = value;
}

void MagicBall::setAutoDestroyTime(const float & value)
{
	mAutoDestroyTime = value;
}

void MagicBall::setSpeed(const float & value)
{
	mSpeed = value;
}

void MagicBall::setTaragetPawn(Pawn & pawn)
{
	mTargetPawn = &pawn;
}
