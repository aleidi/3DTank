#pragma once
#include "Drawable.h"

class CubeForCol : public Drawable
{
public:
	CubeForCol();

	void onUpdate(float deltaTime) noexcept override;
	DirectX::XMMATRIX getTransformXM() const noexcept override;
	Material getMaterial() const noexcept override;

	void Translate(float x, float y, float z);
	void Rotate(float pitch, float yaw, float roll);
	void Scale(float x, float y, float z);
	
private:
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMFLOAT3 scale;
};

