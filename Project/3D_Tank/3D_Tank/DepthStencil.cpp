#include "DepthStencil.h"

DepthStencil::DepthStencil(Graphics & gfx, D3D11_DEPTH_STENCIL_DESC& desc) noexcept
{
	gfx.getDevice()->CreateDepthStencilState(&desc, pDepthState.GetAddressOf());
}

void DepthStencil::bind(Graphics & gfx) noexcept
{
	gfx.getContext()->OMSetDepthStencilState(pDepthState.Get(), 0);
}
