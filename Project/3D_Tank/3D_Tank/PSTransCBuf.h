#pragma once
#include "Bindable.h"
#include "ConstantBuffers.h"
#include "LightHelper.h"
#include "Drawable.h"

class PSTransCBuf : public Bindable
{
public:
	PSTransCBuf(Graphics& gfx, const Drawable& parent);
	void bind(Graphics& gfx) noexcept override;
protected:
	struct CBPS
	{
		Material Mat;
		DirectionalLight DirLight;
		XMFLOAT4 EyePosW;
	};
protected:
	CBPS GetCBPS(Graphics& gfx) noexcept;
private:
	PixelConstantBuffer<CBPS> pcbuf;
	const Drawable& mParent;
};

