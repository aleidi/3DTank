#pragma once
#include "Graphics.h"

using namespace DirectX;

class RenderCamera
{
	enum ProjectionType
	{
		Perspective = 0,
		Orthographic = 1,
	};

public:
	RenderCamera(Graphics* gfx);
	~RenderCamera();

	XMVECTOR getPosition() noexcept;
	void setPosition(XMVECTOR pos) noexcept;
	void setPosition(float x, float y, float z) noexcept;
	XMVECTOR getRotation() noexcept;
	void setRotation(XMVECTOR rot) noexcept;
	void setRotation(float x, float y, float z) noexcept;
	XMVECTOR getRight() noexcept;
	XMVECTOR getUp() noexcept;
	XMVECTOR getForward() noexcept;
	
	XMMATRIX getViewXM() noexcept;
	XMMATRIX getProjectionXM() noexcept;
	XMMATRIX getViewProjXM() noexcept;

	void setFrustum(float nearZ, float farZ, float aspect, float fov) noexcept;
	void setViewport(float topLeftX, float topLeftY, float width, float height, float minDepth, float maxDepth) noexcept;
	/// 0 for Perspective, 1 for Orthographic , default is Perspective mode
	void setProjectionType(int type = 0) noexcept;

protected:
	XMFLOAT3 mPosition;
	XMFLOAT3 mRotation;
	XMFLOAT3 mRight;
	XMFLOAT3 mUp;
	XMFLOAT3 mForward;
	ProjectionType mProjType;
	
	//frustum
	float mFov;
	float mAspect;
	float mNearZ;
	float mFarZ;

	D3D11_VIEWPORT mViewport;
};

