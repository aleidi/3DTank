#include "Texture.h"
#include "DDSTextureLoader.h"

Texture::Texture(Graphics& gfx, const wchar_t * path)
{
	std::wstring str = L".\\Resource\\Model\\";
	str += path;
	str += L".dds";
	CreateDDSTextureFromFile(GetDevice(gfx), str.c_str(), nullptr, pTextureRV.GetAddressOf());
}

void Texture::bind(Graphics & gfx) noexcept
{
	GetContext(gfx)->PSSetShaderResources(0, 1, pTextureRV.GetAddressOf());
}
