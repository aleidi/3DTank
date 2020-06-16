#include "Texture.h"
#include "DDSTextureLoader.h"

Texture::Texture(Graphics& gfx, const std::wstring & path)
{
	std::wstring str = L".\\Resource\\Model\\";
	str += path;
	str += L".dds";
	CreateDDSTextureFromFile(getDevice(gfx), str.c_str(), nullptr, pTextureRV.GetAddressOf());

	if (nullptr == pTextureRV)
	{
		createDefualtTexture(gfx);
	}

}

void Texture::bind(Graphics & gfx) noexcept
{
	GetContext(gfx)->PSSetShaderResources(0, 1, pTextureRV.GetAddressOf());
}

void Texture::createDefualtTexture(Graphics& gfx) noexcept
{
	CreateDDSTextureFromFile(getDevice(gfx), L"./Resource/Model/Objects/DefaultTexture.dds", nullptr, pTextureRV.GetAddressOf());
}
