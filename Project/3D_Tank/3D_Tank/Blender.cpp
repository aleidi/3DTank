#include "Blender.h"

Blender::Blender(Graphics& gfx) noexcept
	: Blender(gfx, BlendMode::Opaque, false)
{
}

Blender::Blender(Graphics& gfx, BlendMode mode, bool alphaToCoverage) noexcept
	: mMode(mode)
{
	createOpaqueState(gfx);
	createAlphaBlendState(gfx, alphaToCoverage);
	createAdditiveState(gfx);
}

void Blender::setMode(BlendMode mode) noexcept
{
	mMode = mode;
}

Blender::BlendMode Blender::getMode() const noexcept
{
	return mMode;
}

void Blender::bind(Graphics& gfx) noexcept
{
	ID3D11BlendState* state = nullptr;

	switch (mMode)
	{
	case BlendMode::Opaque:
		state = mOpaqueBlendState.Get();
		break;
	case BlendMode::AlphaBlend:
		state = mAlphaBlendState.Get();
		break;
	case BlendMode::Additive:
		state = mAdditiveBlendState.Get();
		break;
	default:
		state = mOpaqueBlendState.Get();
		break;
	}

	getContext(gfx)->OMSetBlendState(state, nullptr, 0xFFFFFFFF);
}

void Blender::createOpaqueState(Graphics& gfx) noexcept
{
	D3D11_BLEND_DESC bd = {};
	bd.AlphaToCoverageEnable = false;
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = false;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	gfx.getDevice()->CreateBlendState(&bd, mOpaqueBlendState.GetAddressOf());
}

void Blender::createAlphaBlendState(Graphics& gfx, bool alphaToCoverage) noexcept
{
	D3D11_BLEND_DESC bd = {};
	bd.AlphaToCoverageEnable = alphaToCoverage ? TRUE : FALSE;
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	gfx.getDevice()->CreateBlendState(&bd, mAlphaBlendState.GetAddressOf());
}

void Blender::createAdditiveState(Graphics& gfx) noexcept
{
	D3D11_BLEND_DESC bd = {};
	bd.AlphaToCoverageEnable = false;
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	gfx.getDevice()->CreateBlendState(&bd, mAdditiveBlendState.GetAddressOf());
}
