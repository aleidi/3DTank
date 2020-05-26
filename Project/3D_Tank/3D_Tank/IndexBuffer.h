#pragma once
#include "Bindable.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graphics& gfx, const std::vector<UINT>& indices);
	void bind(Graphics& gfx) noexcept override;
	UINT getCount() const noexcept;
protected:
	UINT mCount;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
};
