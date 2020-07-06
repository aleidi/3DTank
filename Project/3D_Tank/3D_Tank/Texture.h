#pragma once
#include "Bindable.h"

class Texture : public Bindable
{
public:
	Texture(Graphics& gfx);
	Texture(Graphics& gfx, const std::wstring& path, UINT slot = 0);
	void bind(Graphics& gfx) noexcept override;

private:
	void createDefualtTexture(Graphics& gfx) noexcept;

private:
	wchar_t* mPath;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureRV;
	UINT mSlot;
};