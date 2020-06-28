#pragma once
#include "UIText.h"

class UIText3D : public UIText
{
public:
	UIText3D() = default;
	UIText3D(Graphics& gfx);
	UIText3D(Graphics& gfx, std::wstring text);
	DirectX::XMMATRIX getTransformXM() const noexcept override;
	void draw(Graphics& gfx) noexcept override;
};

