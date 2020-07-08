#pragma once
#include "Drawable.h"
#include "ConstantBuffers.h"

class VFXSphere : public Drawable
{
public:
	VFXSphere(Graphics& gfx);
	void onUpdate(float deltaTime) noexcept override;
	DirectX::XMMATRIX getTransformXM() const noexcept override;
	virtual void draw(Graphics& gfx) noexcept override;
	void SetBlendTransparent(Graphics& gfx);
	void ResetBlendState(Graphics& gfx);
	void tileOffset(const float& x, const float& y);
	void setPosition(const float& x, const float& y, const float& z);
	void translate(const float& x, const float& y, const float& z);
	void rotate(const float& pitch, const float& yaw, const float& roll);
	void setRotation(const float& pitch, const float& yaw, const float& roll);
	void setScale(const float& x, const float& y, const float& z);

private:
	float mX;
	float mY;
	float mZ;
	float mRoll;
	float mPitch;
	float mYaw;
	float mTileOffsetX;
	float mTileOffsetY;
	float mScaleX;
	float mScaleY;
	float mScaleZ;

	struct CBVS
	{
		XMMATRIX World;
		XMMATRIX View;
		XMMATRIX Proj;
		XMFLOAT2 Tile;
	};

	std::unique_ptr<PixelConstantBuffer<XMFLOAT4>> mPCB; 
	std::unique_ptr<VertexConstantBuffer<CBVS>> mVCB;
};

