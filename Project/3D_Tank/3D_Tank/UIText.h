#pragma once
#include "UIBase.h"
#include "BindableBase.h"
#include "FreeType.h"

class UIText : public UIBase
{
public:
	UIText() = default;
	UIText(Graphics& gfx);
	UIText(Graphics& gfx, std::wstring text);

	virtual void draw(Graphics& gfx) noexcept override;
	void setText(Graphics& gfx, std::wstring wstr);

protected:
	virtual void setBlendTransparent(Graphics& gfx);
	void resetBlendState(Graphics& gfx);

protected:
	std::wstring mText;
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> pSRVs;
	std::unique_ptr<PixelConstantBuffer<DirectX::XMFLOAT4>> mPCBuf;
	std::vector<FreeType::Character> mChars;
};

