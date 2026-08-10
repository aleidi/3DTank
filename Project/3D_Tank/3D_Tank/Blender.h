#pragma once
#include "Bindable.h"

class Blender : public Bindable
{
public:
	enum class BlendMode
	{
		Opaque = 0,
		AlphaBlend,
		Additive
	};

	Blender(Graphics& gfx) noexcept;
	Blender(Graphics& gfx, BlendMode mode, bool alphaToCoverage = false) noexcept;

	void setMode(BlendMode mode) noexcept;
	BlendMode getMode() const noexcept;

	void bind(Graphics& gfx) noexcept override;

private:
	void createOpaqueState(Graphics& gfx) noexcept;
	void createAlphaBlendState(Graphics& gfx, bool alphaToCoverage) noexcept;
	void createAdditiveState(Graphics& gfx) noexcept;

private:
	BlendMode mMode;
	Microsoft::WRL::ComPtr<ID3D11BlendState> mOpaqueBlendState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> mAlphaBlendState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> mAdditiveBlendState;
};

