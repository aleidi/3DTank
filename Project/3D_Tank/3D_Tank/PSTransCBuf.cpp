#include "PSTransCBuf.h"
#include "RenderManager.h"

PSTransCBuf::PSTransCBuf(Graphics& gfx, const Drawable& parent)
	:
	pcbuf(gfx),
	mParent(parent)
{}

void PSTransCBuf::bind(Graphics& gfx) noexcept
{
	pcbuf.onUpdate(gfx, getCBPS(gfx));

	pcbuf.bind(gfx);
}

PSTransCBuf::CBPS PSTransCBuf::getCBPS(Graphics& gfx) noexcept
{
	XMFLOAT3 cam;
 	XMStoreFloat3(&cam, gfx.getCameraPosition());
	return
	{
		mParent.getMaterial(),
		RenderManager::sGetInstance()->getDirLight(),
		XMFLOAT3(cam.x,cam.y,cam.z),
		0.4f
	};
}
