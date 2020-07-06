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
	void tileOffset(float x, float y);
	void setPosition(float x, float y, float z);
	void translate(float x, float y, float z);
	void rotate(float pitch, float yaw, float roll);
	void setRotation(float pitch, float yaw, float roll);

private:
	float mX;
	float mY;
	float mZ;
	float mRoll;
	float mPitch;
	float mYaw;
	float mTileOffsetX;
	float mTileOffsetY;

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

