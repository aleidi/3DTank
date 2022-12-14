#pragma once
#include "Drawable.h"

class SkyBox : public Drawable
{
public:
	SkyBox(Graphics& gfx);
	SkyBox(Graphics& gfx, const std::wstring& texture);
	void onUpdate(float deltaTime) noexcept override;
	DirectX::XMMATRIX getTransformXM() const noexcept override;
	Material getMaterial() const noexcept override;
	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);

private:
	float mPosX;
	float mPosY;
	float mPosZ;
	float mRotX;
	float mRotY;
	float mRotZ;
};