#pragma once
#include "Drawable.h"

class UIBase : public Drawable
{
public:
	UIBase() = default;
	UIBase(const UIBase&) = delete;

	void onUpdate(float deltaTime) noexcept override;
	virtual void onUpdate(Graphics& gfx, float dt) noexcept;
	virtual DirectX::XMMATRIX getTransformXM() const noexcept override;

	void SetSize(float width, float height) noexcept;
	void SetPosition(float x, float y) noexcept;

protected:
	float mWidth;
	float mHeight;
	float mX;
	float mY;
};

