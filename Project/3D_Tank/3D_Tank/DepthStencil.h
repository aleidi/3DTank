#pragma once
#include "Bindable.h"

class DepthStencil : public Bindable
{
public:
	DepthStencil(Graphics& gfx, D3D11_DEPTH_STENCIL_DESC& desc) noexcept;
	DepthStencil(Graphics& gfx);
	void bind(Graphics& gfx) noexcept override;

private:
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthState;
};

