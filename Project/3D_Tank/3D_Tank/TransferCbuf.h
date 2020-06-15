#pragma once
#include "ConstantBuffers.h"
#include "Drawable.h"
#include <DirectXMath.h>

class TransferCbuf : public Bindable
{
public:
	TransferCbuf(Graphics& gfx, const Drawable& mParent);
	void bind(Graphics& gfx) noexcept override;

protected:
	struct CBWVP
	{
		XMMATRIX World;
		XMMATRIX View;
		XMMATRIX Proj;
		XMMATRIX WorldInvTranspose;
	};
protected:
	CBWVP getMVP(Graphics& gfx) noexcept;
private:
	VertexConstantBuffer<CBWVP> mVertexConstbuff;
	const Drawable& mParent;
};