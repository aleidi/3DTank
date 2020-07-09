#pragma once
#include "GameObject.h"
#include "Vector3.h"


class VFXSphere;
class Pawn;

class MagicBall : public GameObject
{
public:
	MagicBall();
	~MagicBall();

	void onUpdate(const float& deltaTime) override;
	void enableTile(bool value);
	void setColor(const DirectX::XMFLOAT4& color);
	void setTile(const float& x, const float& y);
	void setTarget(const Vector3& target);
	void enableChase(const bool& value);
	void setAutoDestroyTime(const float& value);
	void setSpeed(const float& value);
	void setTaragetPawn(Pawn& pawn);

private:
	VFXSphere* mVFX;

	bool mCanTile;
	float mTileX;
	float mTileY;

	Vector3 mTargetPos;
	bool mCanChase;
	float mTimer;
	float mAutoDestroyTime;
	float mSpeed;
	Pawn* mTargetPawn;
};

