#pragma once
#include "ConstantBuffers.h"
#include "Drawable.h"
#include <DirectXMath.h>

class TransformCbuf : public Bindable
{
public:
	TransformCbuf(Graphics& gfx, const Drawable& mParent);
	void bind(Graphics& gfx) noexcept override;

protected:
	struct ConstantBufferWVP
	{
		XMMATRIX World;
		XMMATRIX View;
		XMMATRIX Proj;
	};
protected:
	ConstantBufferWVP getMVP(Graphics& gfx) noexcept;
private:
	VertexConstantBuffer<ConstantBufferWVP> mVertexConstbuff;
	const Drawable& mParent;
};