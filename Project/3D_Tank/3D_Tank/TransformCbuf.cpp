#include <assert.h>

#include "TransformCbuf.h"

TransformCbuf::TransformCbuf(Graphics& gfx, const Drawable& mParent)
	:
	mVertexConstbuff(gfx),
	mParent(mParent)
{}

void TransformCbuf::bind(Graphics& gfx) noexcept
{

	mVertexConstbuff.Update(gfx,getMVP(gfx));
	mVertexConstbuff.bind(gfx);
}

TransformCbuf::ConstantBufferWVP TransformCbuf::getMVP(Graphics & gfx) noexcept
{
	return
	{
		DirectX::XMMatrixTranspose(mParent.GetTransformXM()),
		DirectX::XMMatrixTranspose(gfx.getView()),
		DirectX::XMMatrixTranspose(gfx.getProj())
	};
}
