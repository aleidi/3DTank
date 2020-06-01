#include "TransformCbuf.h"

TransformCbuf::TransformCbuf(Graphics& gfx, const Drawable& mParent)
	:
	mVertexConstbuff(gfx),
	mParent(mParent)
{}

void TransformCbuf::bind(Graphics& gfx) noexcept
{
	mVertexConstbuff.Update(gfx,
		DirectX::XMMatrixTranspose(
			mParent.GetTransformXM() * gfx.GetViewProj()
		)
	);
	mVertexConstbuff.bind(gfx);
}