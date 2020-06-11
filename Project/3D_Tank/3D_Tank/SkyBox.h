#pragma once
#include "Drawable.h"

class SkyBox : public Drawable
{
public:
	SkyBox(Graphics& gfx);
	void Update(float deltaTime) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void setPosition(float x, float y, float z);

private:
	float mPosX;
	float mPosY;
	float mPosZ;
};

