#include "Sampler.h"

Sampler::Sampler(Graphics & gfx)
{
	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	getDevice(gfx)->CreateSamplerState(&sampDesc, pSamplerState.GetAddressOf());
}

Sampler::Sampler(Graphics & gfx, D3D11_SAMPLER_DESC desc)
{
	getDevice(gfx)->CreateSamplerState(&desc, pSamplerState.GetAddressOf());
}

void Sampler::bind(Graphics & gfx) noexcept
{
	getContext(gfx)->PSSetSamplers(0, 1, pSamplerState.GetAddressOf());
}
