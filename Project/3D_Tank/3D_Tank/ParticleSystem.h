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
public:
	ParticleSystem(Graphics& gfx, const std::wstring& texture, int maxParticles = 1);
	~ParticleSystem();

	void onUpdate(float deltaTime) noexcept override;
	DirectX::XMMATRIX getTransformXM() const noexcept override;
	void draw(Graphics& gfx, float deltaTime) noexcept;

	//説明:
	//使用可能なパーティクルの最大数
	void setMaxPatricles(int value) noexcept;

	//説明:
	//パーティクルを放出する形状
	void setEmitter(Emitter type);

	//説明:
	//パーティクルの生存時間
	void setLifeTime(float value);
	
	//説明:
	//xはピッチ、yはヨー、zはロール
	void setStartRotation(float x, float y, float z);

	//説明:
	//パーティクルの初期スケール
	//xは幅、yは高さ、zは現在未使用
	void setStartScale(float x, float y, float z);

	//説明:
	//パーティクルの初期位置
	void setPosition(float x, float y, float z);

	//説明:
	//xはエミッターの幅、yは高さ、zは奥行き
	void setRange(float x, float y, float z);

	//説明:
	//パーティクルの速度をminからmaxの範囲に設定
	//maxとminが等しい場合、速度はminになる
	void setMaxMinSpeed(float max, float min);

	//説明:
	//xは水平方向、yは垂直方向の最大タイル数
	void setTile(float x, float y);

	//説明:
	//スプライト間の切り替え間隔
	void setAnimationInterval(float value);

	//説明:
	//xは水平方向、yは垂直方向のタイル移動量
	void setTileStep(float x, float y);

	//説明:
	//1秒あたりのパーティクル放出数
	void setEmitRate(int value);

	//説明:
	//パーティクルの初速度
	void setVelocity(float x, float y, float z);
	
	//説明:
	//パーティクルシステムを有効化
	void play();

	//説明:
	//パーティクルシステムを無効化
	void stop();

	//ループしない場合の1回分の再生時間
	void setDuration(float value);

	//パーティクルをループ再生するか設定
	void enableLoop(bool value);

	const std::vector<PAttribute>& getParticles();

protected:
	struct VertexPosSize
	{
		XMFLOAT3 Position;
		XMFLOAT2 Size;
		XMFLOAT4 Tile;
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

	//スプライトアニメーションのパラメーター
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