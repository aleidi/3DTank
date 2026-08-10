#pragma once
#include "Drawable.h"

class UIBase : public Drawable
{
public:
	UIBase() = default;
	UIBase(const UIBase&) = delete;

	enum class UIBlendMode
	{
		Additive = 0,   // ????????
		AlphaBlend = 1
	};

	void onUpdate(float deltaTime) noexcept override;
	virtual DirectX::XMMATRIX getTransformXM() const noexcept override;

	void setSize(float width, float height) noexcept;
	void setPosition(float x, float y, float z) noexcept;
	void setPosition(float x, float y) noexcept;
	void getPosition(float& x, float& y, float& z) noexcept;
	void getPosition(float& x, float& y) noexcept;
	void setEnable(bool value) noexcept;
	void setRotation(float pitch, float yaw, float roll, bool isDeg = false);
	void rotate(float x, float y, float z);
	void setBlend(bool value);

	void setBlendMode(UIBlendMode mode) noexcept;
	UIBlendMode getBlendMode() const noexcept;

protected:
	virtual void setBlendTransparent(Graphics& gfx);
	void resetBlendState(Graphics& gfx);

protected:
	float mWidth = 0.0f;
	float mHeight = 0.0f;
	float mX = 0.0f;
	float mY = 0.0f;
	float mZ = 0.0f;
	float mPitch = 0.0f;
	float mYaw = 0.0f;
	float mRoll = 0.0f;
	bool mIsEnable = false;
	bool mCanBlend = false;
	UIBlendMode mBlendMode = UIBlendMode::Additive;
};

