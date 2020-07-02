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
		XMFLOAT3 EyePosW;
		float Fresnel;
	};
protected:
	CBPS getCBPS(Graphics& gfx) noexcept;
private:
	PixelConstantBuffer<CBPS> pcbuf;
	const Drawable& mParent;
};

