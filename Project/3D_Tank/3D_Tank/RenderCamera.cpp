#include "RenderCamera.h"
#include "Window.h"

RenderCamera::RenderCamera(const Graphics& gfx)
	: mPosition(0.0f,0.0f,0.0f), mRotation(0.0f,0.0f,0.0f),
	mRight(1.0f,0.0f,0.0f),mUp(0.0f,0.0f,1.0f),mForward(0.0f,0.0f,1.0f),
	mProjType(ProjectionType::Perspective),mFov(XM_PI/3),mAspect(WINDOW_WIDTH/WINDOW_HEIGHT),mNearZ(0.1f),mFarZ(1000.0f),
	mViewport{ 0.0f,0.0f, (float)gfx.mClientWidth,(float)gfx.mClientWidth,0.0f,1.0f}
{
}

RenderCamera::~RenderCamera()
{
}

XMVECTOR RenderCamera::getPosition() noexcept
{
	XMVECTOR v;
	v = XMLoadFloat3(&mPosition);
	return v;
}

void RenderCamera::setPosition(XMVECTOR pos) noexcept
{
	XMStoreFloat3(&mPosition, pos);
}

void RenderCamera::setPosition(float x, float y, float z) noexcept
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}

XMVECTOR RenderCamera::getRotation() noexcept
{
	XMVECTOR v;
	v = XMLoadFloat3(&mRotation);
	return v;
}

void RenderCamera::setRotation(XMVECTOR rot) noexcept
{
	XMStoreFloat3(&mRotation, rot);
}

void RenderCamera::setRotation(float x, float y, float z) noexcept
{
	mRotation.x = x;
	mRotation.y = y;
	mRotation.z = z;
}

XMVECTOR RenderCamera::getRight() noexcept
{
	XMVECTOR v;
	v = XMLoadFloat3(&mRight);
	return v;
}

XMVECTOR RenderCamera::getUp() noexcept
{
	XMVECTOR v;
	v = XMLoadFloat3(&mUp);
	return v;
}

XMVECTOR RenderCamera::getForward() noexcept
{
	XMVECTOR v;
	v = XMLoadFloat3(&mForward);
	return v;
}

XMMATRIX RenderCamera::getViewXM() noexcept
{
	return XMMatrixRotationRollPitchYaw(mRotation.z, mRotation.x, mRotation.x) *
		XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);
}

XMMATRIX RenderCamera::getProjectionXM() noexcept
{
	if (mProjType == ProjectionType::Orthographic)
	{
		return XMMatrixOrthographicLH(1.0f, mAspect, mNearZ, mFarZ);
	}

	return XMMatrixPerspectiveFovLH(mFov, mAspect, mNearZ, mFarZ);
}

XMMATRIX RenderCamera::getViewProjXM() noexcept
{
	return getViewXM()*getProjectionXM();
}

void RenderCamera::setFrustum(float nearZ, float farZ, float aspect, float fov) noexcept
{
	mNearZ = nearZ;
	mFarZ = farZ;
	mAspect = aspect;
	mFov = fov;
}

void RenderCamera::setViewport(float topLeftX, float topLeftY, float width, float height, float minDepth, float maxDepth) noexcept
{
	mViewport.TopLeftX = topLeftX;
	mViewport.TopLeftY = topLeftY;
	mViewport.Width = width;
	mViewport.Height = height;
	mViewport.MinDepth = minDepth;
	mViewport.MaxDepth = maxDepth;
}

void RenderCamera::setProjectionType(int type) noexcept
{
	mProjType = (ProjectionType)type;
	if (mProjType != ProjectionType::Perspective || mProjType != ProjectionType::Orthographic)
	{
		mProjType = ProjectionType::Perspective;
	}
}
