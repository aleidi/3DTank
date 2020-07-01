#include "UIBase.h"

void UIBase::onUpdate(float deltaTime) noexcept
{
}

DirectX::XMMATRIX UIBase::getTransformXM() const noexcept
{
	return XMMatrixRotationRollPitchYaw(mPitch, mYaw, mRoll)*
		XMMatrixTranslation(0.5f, 0.5f, 0.0f)*
		XMMatrixScaling(mWidth, mHeight, 0.0f)*
		XMMatrixTranslation(mX, mY, 0.0f)*
		XMMatrixScaling(2.0f / (float)WINDOW_WIDTH, 2.0f / (float)WINDOW_HEIGHT, 0.0f)*
		XMMatrixTranslation(-1.0f, -1.0f, 0.0f);
}

void UIBase::setSize(float width, float height) noexcept
{
	mWidth = width;
	mHeight = height;
}

void UIBase::setPosition(float x, float y, float z) noexcept
{
	mX = x;
	mY = y;
	mZ = z;
}

void UIBase::setPosition(float x, float y) noexcept
{
	mX = x;
	mY = y;
}

void UIBase::getPosition(float & x, float & y, float & z) noexcept
{
	x = mX;
	y = mY;
	z = mZ;
}

void UIBase::getPosition(float & x, float & y) noexcept
{
	x = mX;
	y = mY;
}

void UIBase::setEnable(bool value) noexcept
{
	mIsEnable = value;
}

void UIBase::setRotation(float pitch, float yaw, float roll, bool isDeg)
{
	if (isDeg != true)
	{
		mPitch = pitch;
		mYaw = yaw;
		mRoll = roll;
		return;
	}

	mPitch = XMConvertToRadians(pitch);
	mYaw = XMConvertToRadians(yaw);
	mRoll = XMConvertToRadians(roll);
}

void UIBase::rotate(float x, float y, float z)
{
	mPitch += x;
	mYaw += y;
	mRoll += z;
}

void UIBase::setBlend(bool value)
{
	mCanBlend = value;
}

void UIBase::setBlendTransparent(Graphics & gfx)
{
	Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState;
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.AlphaToCoverageEnable = true;
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	gfx.getDevice()->CreateBlendState(&bd, pBlendState.GetAddressOf());
	gfx.getContext()->OMSetBlendState(pBlendState.Get(), nullptr, 0xFFFFFFFF);
}

void UIBase::resetBlendState(Graphics & gfx)
{
	Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState;
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.AlphaToCoverageEnable = true;
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	gfx.getDevice()->CreateBlendState(&bd, pBlendState.GetAddressOf());
	gfx.getContext()->OMSetBlendState(pBlendState.Get(), nullptr, 0xFFFFFFFF);
}

