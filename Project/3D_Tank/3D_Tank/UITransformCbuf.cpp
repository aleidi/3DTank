#include "UITransformCbuf.h"

UITransformCbuf::UITransformCbuf(Graphics& gfx, const UIBase& parent)
	:mVCB(gfx),
	mParent(parent)
{}

void UITransformCbuf::bind(Graphics& gfx) noexcept
{
	mVCB.onUpdate(gfx, DirectX::XMMatrixTranspose(mParent.getTransformXM()));
	mVCB.bind(gfx);
}