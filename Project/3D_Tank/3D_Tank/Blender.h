#pragma once
#include "Bindable.h"

class Blender : public Bindable
{
public:
	Blender(Graphics& gfx) noexcept;
	void bind(Graphics& gfx) noexcept override;
private:
	Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState;
};

