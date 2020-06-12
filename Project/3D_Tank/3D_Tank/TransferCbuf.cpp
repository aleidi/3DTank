#include <assert.h>

#include "TransferCbuf.h"

TransferCbuf::TransferCbuf(Graphics& gfx, const Drawable& mParent)
	:
	mVertexConstbuff(gfx),
	mParent(mParent)
{}

void TransferCbuf::bind(Graphics& gfx) noexcept
{
	mVertexConstbuff.onUpdate(gfx,getMVP(gfx));
	mVertexConstbuff.bind(gfx);
}

TransferCbuf::CBWVP TransferCbuf::getMVP(Graphics & gfx) noexcept
{
	return
	{
		DirectX::XMMatrixTranspose(mParent.getTransformXM()),
		DirectX::XMMatrixTranspose(gfx.getView()),
		DirectX::XMMatrixTranspose(gfx.getProj())
	};
}
