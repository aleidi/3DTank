#include "UIBase.h"

void UIBase::onUpdate(float deltaTime) noexcept
{
}

DirectX::XMMATRIX UIBase::getTransformXM() const noexcept
{
	return XMMatrixScaling(mWidth, mHeight, 0.0f)*
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

void UIBase::setEnable(bool value) noexcept
{
	mIsEnable = value;
}