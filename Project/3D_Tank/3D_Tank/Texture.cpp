#include "Texture.h"
#include "DDSTextureLoader.h"

Texture::Texture(Graphics& gfx, const wchar_t * path)
{
	CreateDDSTextureFromFile(GetDevice(gfx), path, nullptr, pTextureRV.GetAddressOf());
}

void Texture::bind(Graphics & gfx) noexcept
{
	GetContext(gfx)->PSSetShaderResources(0, 1, pTextureRV.GetAddressOf());
}
