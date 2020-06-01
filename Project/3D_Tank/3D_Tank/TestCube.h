#pragma once
#include "Drawable.h"

class TestCube : public Drawable
{
public:
	TestCube(Graphics& gfx) :TestCube(gfx, 0) {}
	TestCube(Graphics& gfx, UINT id);
	~TestCube();
	void Update(float deltaTime) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

	void Translate(float x, float y, float z);
	void Rotate(float pitch, float yaw, float roll);
	void Scale(float x, float y, float z);
private:
	// positional
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMFLOAT3 scale;
	//float roll = 0.0f;
	//float pitch = 0.0f;
	//float yaw = 0.0f;
	//float theta;
	//float phi;
	//float chi;
	//// speed (delta/s)
	//float droll;
	//float dpitch;
	//float dyaw;
	//float dtheta;
	//float dphi;
	//float dchi;
};

