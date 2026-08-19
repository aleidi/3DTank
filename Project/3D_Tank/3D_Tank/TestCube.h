#pragma once
#include "Drawable.h"

class TestCube : public Drawable
{
public:
	TestCube(Graphics& gfx);
	~TestCube();
	void onUpdate(float deltaTime) noexcept override;
	DirectX::XMMATRIX getTransformXM() const noexcept override;
	Material getMaterial() const noexcept override;

	void Translate(float x, float y, float z);
	void Rotate(float pitch, float yaw, float roll);
	void Scale(float x, float y, float z);
private:
	//位置情報
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMFLOAT3 scale;
	//float roll = 0.0f;
	//float pitch = 0.0f;
	//float yaw = 0.0f;
	//float theta;
	//float phi;
	//float chi;
	////速度（変化量/秒）
	//float droll;
	//float dpitch;
	//float dyaw;
	//float dtheta;
	//float dphi;
	//float dchi;
};

