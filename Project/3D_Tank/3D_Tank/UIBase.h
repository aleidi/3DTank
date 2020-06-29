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
	void setPosition(float x, float y, float z) noexcept;
	void setPosition(float x, float y) noexcept;
	void setEnable(bool value) noexcept;
	void setRotation(float pitch, float yaw, float roll);
	void rotate(float x, float y, float z);
	void setBlend(bool value);

protected:
	virtual void setBlendTransparent(Graphics& gfx);
	void resetBlendState(Graphics& gfx);

protected:
	float mWidth;
	float mHeight;
	float mX;
	float mY;
	float mZ;
	float mPitch;
	float mYaw;
	float mRoll;
	bool mIsEnable;
	bool mCanBlend;
};

