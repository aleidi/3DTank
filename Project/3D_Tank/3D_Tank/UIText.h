#pragma once
#include "UIBase.h"
#include "BindableBase.h"
#include "FreeType.h"

class UIText : public UIBase
{
public:
	UIText(Graphics& gfx);
	UIText(Graphics& gfx, std::wstring text);

	void draw(Graphics& gfx) noexcept override;
	void setText(Graphics& gfx, std::wstring wstr);
private:
	void setBlendTransparent(Graphics& gfx);
	void resetBlendState(Graphics& gfx);
private:
	Graphics& mgfx;
	std::wstring mText;
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> pSRVs;
	std::vector<FreeType::Character> mChars;
};

