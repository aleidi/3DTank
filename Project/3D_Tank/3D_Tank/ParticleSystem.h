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
	void updateParticle(Graphics& gfx, float deltaTime) noexcept;
	void draw(Graphics& gfx, float deltaTime) noexcept;
	void setMaxPatricles(int value) noexcept;
	void setEmitter(Emitter type);
	void setLifeTime(float value);
	void setStartRotation(float x, float y, float z);
	void setStartScale(float x, float y, float z);
	void setPosition(float x, float y, float z);

protected:
	struct VertexPosSize
	{
		XMFLOAT3 Position;
		XMFLOAT2 Size;
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
	};

	struct CBGS
	{
		XMMATRIX View;
		XMMATRIX Proj;
		XMFLOAT3 EyePosW;
	};

	void ResetParticle(PAttribute* p);
	void SetBlendTransparent(Graphics& gfx);
	void ResetBlendState(Graphics& gfx);

protected:

	int mMaxParticles = 500;
	float mLifeTime = 15;
	float mEmitRate = 3;
	int mNeedParticles = mLifeTime * mEmitRate;
	float mStepTime;
	float mDuration;
	float mIsLoop;
	float mStartSpeed = 1.0f;
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