#include <string>
#include "RenderCamera.h"
#include "Window.h"
#include "Camera.h"

#include "Engine.h"

bool RenderCamera::mIsLockOn = false;
XMFLOAT3 RenderCamera::mLockTarget = XMFLOAT3(0.0f,0.0f,1.0f);

RenderCamera::RenderCamera(const Graphics& gfx)
	: mPosition(0.0f,0.0f,0.0f), mRotation(0.0f,0.0f,0.0f),
	mRight(1.0f,0.0f,0.0f),mUp(0.0f,1.0f,0.0f),mForward(0.0f,0.0f,1.0f),
	mProjType(ProjectionType::Perspective),mFov(XM_PI/3),mAspect((float)WINDOW_WIDTH/WINDOW_HEIGHT),mNearZ(0.1f),mFarZ(1000.0f),
	mViewport{ 0.0f,0.0f, (float)gfx.mClientWidth,(float)gfx.mClientWidth,0.0f,1.0f},
	mViewUp(0.0f,1.0f,0.0f)
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

	calculateViewUP();
	calculateDirectionVector();
}

void RenderCamera::setRotation(float x, float y, float z) noexcept
{
	mRotation.x = x;
	mRotation.y = y;
	mRotation.z = z;

	calculateViewUP();
	calculateDirectionVector();
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
	const DirectX::XMVECTOR forwardBaseVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	// apply the camera rotations to a base vector
	const auto lookVector = XMVector3Transform(forwardBaseVector,
		XMMatrixRotationRollPitchYaw(mRotation.x, mRotation.y, mRotation.z));

	const auto camPosition = XMLoadFloat3(&mPosition);
	XMVECTOR camTarget;
	if (!mIsLockOn)
	{
		camTarget = camPosition + lookVector;
	}
	else
	{
		camTarget = XMLoadFloat3(&mLockTarget);
	}

	auto vec = XMVector3LengthSq(XMVectorSubtract(camTarget, camPosition));
	if (XMVector3Equal(vec,XMVectorZero()))
	{
		return XMMatrixLookAtLH(camPosition, XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), XMLoadFloat3(&mViewUp));
	}

	return XMMatrixLookAtLH(camPosition, camTarget, XMLoadFloat3(&mViewUp));
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

void RenderCamera::setLockTarget(float x, float y, float z)
{
	mIsLockOn = true;
	mLockTarget.x = x;
	mLockTarget.y = y;
	mLockTarget.z = z;
}

void RenderCamera::unlockTarget()
{
	mIsLockOn = false;
}

void RenderCamera::onUpdate(const float& deltaTime) noexcept
{
	if (nullptr == Camera::MainCamera)
	{
		mPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
		mRotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
		mProjType = ProjectionType::Perspective;
		mFov = XM_PI / 3;
		mAspect = (float)(WINDOW_WIDTH / WINDOW_HEIGHT);
		mNearZ = 0.1f;
		mFarZ = 1000.0f;
		return;
	}
	setPosition(Camera::MainCamera->Position.x, Camera::MainCamera->Position.y, Camera::MainCamera->Position.z);
	setRotation(Camera::MainCamera->Rotation.x, Camera::MainCamera->Rotation.y, Camera::MainCamera->Rotation.z);
	mFov = Camera::MainCamera->Fov;
	mAspect = Camera::MainCamera->Aspect;
	mNearZ = Camera::MainCamera->Near;
	mFarZ = Camera::MainCamera->Far;
	Camera::MainCamera->IsPerpective ? setProjectionType(ProjectionType::Perspective) : 
		setProjectionType(ProjectionType::Orthographic);

	////test code
	//std::wstring wc = L"RenderCamPosition: ";
	//wc += std::to_wstring(mPosition.x);
	//wc += L"," + std::to_wstring(mPosition.y) + L"," + std::to_wstring(mPosition.z);

	//Engine::sGetInstance()->showtText(wc.c_str(), 0, 0, 600, 600, true);
}

void RenderCamera::calculateDirectionVector() noexcept
{
	XMMATRIX matrix = XMMatrixRotationRollPitchYaw(mRotation.x, mRotation.y, mRotation.z);
	//calculate forward vector
	XMVECTOR v = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	v = XMVector3Transform(v, matrix);
	XMStoreFloat3(&mForward, v);

	//calculate right vector
	v = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	v = XMVector3Transform(v, matrix);
	XMStoreFloat3(&mRight, v);

	//calculate up vector
	v = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	v = XMVector3Transform(v, matrix);
	XMStoreFloat3(&mUp, v);
}

void RenderCamera::calculateViewUP() noexcept
{
	auto result = std::fmodf(mRotation.x + XM_PIDIV2, XM_2PI);
	if (result >= XM_PI || (result <= 0 && result >= -XM_PI))
	{
		mViewUp.y = -1.0f;
	}
	else
	{
		mViewUp.y = 1.0f;
	}
}
