#pragma once
#include "Drawable.h"
#include "BindableBase.h"

using namespace DirectX;

class ParticleSystem : public Drawable
{
public:
	enum Emitter
	{
		NoEmit = 0,
		Box = 1,
	};
public:
	ParticleSystem(Graphics& gfx, const std::wstring& texture);
	~ParticleSystem();

	void onUpdate(float deltaTime) noexcept override;
	DirectX::XMMATRIX getTransformXM() const noexcept override;
	void draw(Graphics& gfx, float deltaTime) noexcept;

	//Explanation:
	//the max amount of particles can be used
	void setMaxPatricles(int value) noexcept;

	//Explanation:
	//the shape particles will be emitted
	void setEmitter(Emitter type);

	//Explanation:
	//the time particles will be alive
	void setLifeTime(float value);
	
	//Explanation:
	//x for pitch, y for yaw, z for roll
	void setStartRotation(float x, float y, float z);

	//Explanation:
	//it is the start scale of particle
	//x for width, y for height, z is unused now
	void setStartScale(float x, float y, float z);

	//Explanation:
	//it is the start position of particle
	void setPosition(float x, float y, float z);

	//Explanation:
	//paricle's velocity will be in the range of (max,min)
	//if max == min, the speed will be min
	void setMaxMinSpeed(float max, float min);

	//Explanation:
	//x is the max horizontal tile amount, y is the max vertical tile amount
	void setTile(float x, float y);

	//Explanation:
	//the step time between two sprite
	void setAnimationInterval(float value);

	//Explanation:
	//x for the horizontal tile step, y for the vertical step
	void setTileStep(float x, float y);

protected:
	struct VertexPosSize
	{
		XMFLOAT3 Position;
		XMFLOAT2 Size;
		XMFLOAT4 Tile;
	};

	struct PSprite
	{
		float CurrentTileX;
		float CurrentTileY;
		float TileCount;
	};

	struct PAttribute
	{
		bool IsAlive;
		float AliveTime;
		XMFLOAT3 Velocity;
		XMFLOAT3 Size;
		XMFLOAT3 Rotation;
		XMFLOAT3 Position;
		XMFLOAT4 Color;
		PSprite Sprite;
	};

	struct CBGS
	{
		XMMATRIX View;
		XMMATRIX Proj;
		XMFLOAT3 EyePosW;
	};

	void resetParticle(PAttribute* p);
	void setBlendTransparent(Graphics& gfx);
	void resetBlendState(Graphics& gfx);
	void updateSprite(PAttribute* p, float deltaTime);
	void updateParticle(Graphics& gfx, float deltaTime) noexcept;

protected:

	int mMaxParticles = 500;
	float mLifeTime = 15;
	float mEmitRate = 3;
	int mNeedParticles = mLifeTime * mEmitRate;
	float mStepTime;
	float mDuration;
	float mIsLoop;
	float mStartSpeed = 1.0f;
	float mMaxSpeed = 3.0f;
	float mMinSpeed = 1.0f;

	//sprite animation param
	float mMaxTileX = 1.0f;
	float mMaxTileY = 1.0f;
	float mTileInterval = 0.1f;
	float mTileStepX = 1;
	float mTileStepY = 1;

	Emitter mEmitter;
	XMFLOAT3 mPosition = XMFLOAT3(0.0f, 0.0f, 5.0f);
	XMFLOAT3 mRotation = XMFLOAT3(90.0f, 0.0f, 0.0f);
	XMFLOAT3 mScale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	XMFLOAT3 mStartRotation;
	XMFLOAT3 mStartScale = XMFLOAT3(10.0f, 10.0f, 10.0f);
	std::vector<PAttribute> mParticles;
	std::unique_ptr<VertexBuffer> mVB;
	std::unique_ptr<GeometryConstantBuffer<CBGS>> mGSCBuf;
	std::unique_ptr<PixelConstantBuffer<XMFLOAT4>> mPCBuf;
};