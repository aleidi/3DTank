#include "DepthStencil.h"

DepthStencil::DepthStencil(Graphics& gfx)
	: DepthStencil(gfx, DepthMode::DepthWrite)
{
}

DepthStencil::DepthStencil(Graphics& gfx, DepthMode mode) noexcept
	: mMode(mode)
{
	createDepthWriteState(gfx);
	createDepthReadOnlyState(gfx);
	createDepthDisabledState(gfx);
}

DepthStencil::DepthStencil(Graphics& gfx, const D3D11_DEPTH_STENCIL_DESC& desc) noexcept
	: mMode(DepthMode::DepthWrite)
{
	gfx.getDevice()->CreateDepthStencilState(&desc, mDepthWriteState.GetAddressOf());
}

void DepthStencil::setMode(DepthMode mode) noexcept
{
	mMode = mode;
}

DepthStencil::DepthMode DepthStencil::getMode() const noexcept
{
	return mMode;
}

void DepthStencil::bind(Graphics& gfx) noexcept
{
	ID3D11DepthStencilState* state = nullptr;

	switch (mMode)
	{
	case DepthMode::DepthWrite:
		state = mDepthWriteState.Get();
		break;
	case DepthMode::DepthReadOnly:
		state = mDepthReadOnlyState.Get();
		break;
	case DepthMode::DepthDisabled:
		state = mDepthDisabledState.Get();
		break;
	default:
		state = mDepthWriteState.Get();
		break;
	}

	gfx.getContext()->OMSetDepthStencilState(state, 0);
}

void DepthStencil::createDepthWriteState(Graphics& gfx) noexcept
{
	D3D11_DEPTH_STENCIL_DESC dd = {};
	dd.DepthEnable = true;
	dd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dd.StencilEnable = false;
	gfx.getDevice()->CreateDepthStencilState(&dd, mDepthWriteState.GetAddressOf());
}

void DepthStencil::createDepthReadOnlyState(Graphics& gfx) noexcept
{
	D3D11_DEPTH_STENCIL_DESC dd = {};
	dd.DepthEnable = true;
	dd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dd.StencilEnable = false;
	gfx.getDevice()->CreateDepthStencilState(&dd, mDepthReadOnlyState.GetAddressOf());
}

void DepthStencil::createDepthDisabledState(Graphics& gfx) noexcept
{
	D3D11_DEPTH_STENCIL_DESC dd = {};
	dd.DepthEnable = false;
	dd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dd.DepthFunc = D3D11_COMPARISON_ALWAYS;
	dd.StencilEnable = false;
	gfx.getDevice()->CreateDepthStencilState(&dd, mDepthDisabledState.GetAddressOf());
}
