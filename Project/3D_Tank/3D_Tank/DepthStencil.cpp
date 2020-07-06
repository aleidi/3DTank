#include "DepthStencil.h"

DepthStencil::DepthStencil(Graphics & gfx, D3D11_DEPTH_STENCIL_DESC& desc) noexcept
{
	gfx.getDevice()->CreateDepthStencilState(&desc, pDepthState.GetAddressOf());
}

DepthStencil::DepthStencil(Graphics & gfx)
{
	D3D11_DEPTH_STENCIL_DESC dd;
	dd.DepthEnable = true;
	dd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dd.StencilEnable = false;
	gfx.getDevice()->CreateDepthStencilState(&dd, pDepthState.GetAddressOf());
}

void DepthStencil::bind(Graphics & gfx) noexcept
{
	gfx.getContext()->OMSetDepthStencilState(pDepthState.Get(), 0);
}
