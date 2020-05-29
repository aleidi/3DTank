#pragma once
#include "ConstantBuffers.h"
#include "Drawable3D.h"
#include <DirectXMath.h>

class TransformCbuf : public Bindable
{
public:
	TransformCbuf(Graphics& gfx, const Drawable3D& mParent);
	void bind(Graphics& gfx) noexcept override;
private:
	VertexConstantBuffer<DirectX::XMMATRIX> mVertexConstbuff;
	const Drawable3D& mParent;
};