#pragma once
#include <array>

#include "UIBase.h"
#include "ConstantBuffers.h"

class UIButton : public UIBase
{
public:
	enum State
	{
		Normal = 0,
		Selected = 1,
		Pressed = 2,
	};

	UIButton(Graphics& gfx);
	UIButton(Graphics& gfx, const std::wstring& texPath);

	void draw(Graphics& gfx) const noexcept override;
	void checkState(float x, float y, bool isPressed);
	void setColor(XMFLOAT4 color, State btnState);

private:

	void onNormal();
	void onSelected();
	void onPressed();
private:
	State mBtnState;
	std::array<XMFLOAT4, 3> mColors;
	std::unique_ptr<PixelConstantBuffer<XMFLOAT4>> mPCBuf;

};

