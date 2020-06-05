#pragma once
#include "Bindable.h"

class Sampler : public Bindable
{
public:
	Sampler(Graphics& gfx);
	Sampler(Graphics& gfx, D3D11_SAMPLER_DESC desc);
	void bind(Graphics& gfx) noexcept override;
private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSamplerState;
};

