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
	ParticleSystem(Graphics& gfx, const std::wstring& texture, int maxParticles = 1);
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
	//x is the width of emitter, y is the height of the emitter, z is the depth of emiiter
	void setRange(float x, float y, float z);

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

	//Explanation:
	//particles emited per seconds
	void setEmitRate(int value);

	//Explanation:
	//the start velocity  of particle
	void setVelocity(float x, float y, float z);
	
	//Explanation:
	//active particle system
	void play();

	//Explanation:
	//deactive particle system
	void stop();

	//if is not loop, the duration particle play once time
	void setDuration(float value);

	//set whether particle will loop
	void enableLoop(bool value);


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
	void updateParticle(Graphics& gfx, float deltaTime, int& deathPatricles) noexcept;
	void calculateNeedParticle();

protected:

	int mMaxParticles;
	float mLifeTime;
	int mEmitRate;
	int mNeedParticles;
	float mStepTime;
	float mDuration;
	float mTimeCount;
	float mIsLoop;
	float mStartSpeed;
	float mMaxSpeed;
	float mMinSpeed;
	XMFLOAT3 mStartVelocity;

	//sprite animation param
	float mMaxTileX;
	float mMaxTileY;
	float mTileInterval;
	float mTileStepX;
	float mTileStepY;

	Emitter mEmitter;
	XMFLOAT3 mPosition;
	XMFLOAT3 mRotation;
	XMFLOAT3 mScale;
	XMFLOAT3 mStartRotation;
	XMFLOAT3 mStartScale;
	bool mIsActivate;

	std::vector<PAttribute> mParticles;
	std::unique_ptr<VertexBuffer> mVB;
	std::unique_ptr<GeometryConstantBuffer<CBGS>> mGSCBuf;
	std::unique_ptr<PixelConstantBuffer<XMFLOAT4>> mPCBuf;
};