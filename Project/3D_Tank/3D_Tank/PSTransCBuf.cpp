#include "PSTransCBuf.h"
#include "RenderManager.h"

PSTransCBuf::PSTransCBuf(Graphics& gfx, const Drawable& parent)
	:
	pcbuf(gfx),
	mParent(parent)
{}

void PSTransCBuf::bind(Graphics& gfx) noexcept
{
	pcbuf.onUpdate(gfx, GetCBPS(gfx));

	pcbuf.bind(gfx);
}

PSTransCBuf::CBPS PSTransCBuf::GetCBPS(Graphics& gfx) noexcept
{
	XMFLOAT3 cam;
	XMStoreFloat3(&cam, gfx.getCameraPosition());
	return
	{
		mParent.GetMaterial(),
		RenderManager::sGetInstance()->getDirLight(),
		XMFLOAT4(cam.x,cam.y,cam.z,1.0f)
	};
}
