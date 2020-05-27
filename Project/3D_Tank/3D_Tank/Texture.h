#pragma once
#include "Bindable.h"

class Texture : public Bindable
{
public:
	Texture(Graphics& gfx, const wchar_t* path);
	void bind(Graphics& gfx) noexcept override;
private:
	wchar_t* mPath;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureRV;
};