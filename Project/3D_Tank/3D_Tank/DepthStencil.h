#pragma once
#include "Bindable.h"

class DepthStencil : public Bindable
{
public:
	enum class DepthMode
	{
		DepthWrite = 0,
		DepthReadOnly,
		DepthDisabled
	};

	DepthStencil(Graphics& gfx);
	DepthStencil(Graphics& gfx, DepthMode mode) noexcept;
	DepthStencil(Graphics& gfx, const D3D11_DEPTH_STENCIL_DESC& desc) noexcept;

	void setMode(DepthMode mode) noexcept;
	DepthMode getMode() const noexcept;

	void bind(Graphics& gfx) noexcept override;

private:
	void createDepthWriteState(Graphics& gfx) noexcept;
	void createDepthReadOnlyState(Graphics& gfx) noexcept;
	void createDepthDisabledState(Graphics& gfx) noexcept;

private:
	DepthMode mMode;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDepthWriteState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDepthReadOnlyState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDepthDisabledState;
};

