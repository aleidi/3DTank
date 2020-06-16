#include "Rasterizer.h"

Rasterizer::Rasterizer(Graphics & gfx) noexcept
{
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.FrontCounterClockwise = false;
	rd.DepthClipEnable = true;
	gfx.getDevice()->CreateRasterizerState(&rd, pRasterizerState.GetAddressOf());
}

Rasterizer::Rasterizer(Graphics & gfx, D3D11_RASTERIZER_DESC desc) noexcept
{
	gfx.getDevice()->CreateRasterizerState(&desc, pRasterizerState.GetAddressOf());
}

void Rasterizer::bind(Graphics & gfx) noexcept
{
	GetContext(gfx)->RSSetState(pRasterizerState.Get());
}
