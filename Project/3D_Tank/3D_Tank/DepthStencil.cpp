#include "DepthStencil.h"

DepthStencil::DepthStencil(Graphics & gfx, D3D11_DEPTH_STENCIL_DESC& desc) noexcept
{
	gfx.GetDevice()->CreateDepthStencilState(&desc, pDepthState.GetAddressOf());
}

void DepthStencil::bind(Graphics & gfx) noexcept
{
	gfx.GetContext()->OMSetDepthStencilState(pDepthState.Get(), 0);
}
