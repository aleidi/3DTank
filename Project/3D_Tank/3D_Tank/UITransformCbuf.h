#pragma once

#include "UIBase.h"
#include "ConstantBuffers.h"

class UITransformCbuf : public Bindable
{
public:
	UITransformCbuf(Graphics& gfx, const UIBase& parent);
	void bind(Graphics& gfx) noexcept override;

private:
	VertexConstantBuffer<XMMATRIX> mVCB;
	const UIBase& mParent;
};
