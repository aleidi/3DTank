#pragma once
#include "Drawable.h"

class UIBase : public Drawable
{
public:
	UIBase() = default;
	UIBase(const UIBase&) = delete;

	void onUpdate(float deltaTime) noexcept override;
	virtual DirectX::XMMATRIX getTransformXM() const noexcept override;

	void setSize(float width, float height) noexcept;
	void setPosition(float x, float y) noexcept;
	void setEnable(bool value) noexcept;

protected:
	float mWidth;
	float mHeight;
	float mX;
	float mY;
	bool mIsEnable;
};

