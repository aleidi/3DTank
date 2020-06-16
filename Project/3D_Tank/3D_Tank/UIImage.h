#pragma once
#include "UIBase.h"
#include "UICommon.h"
#include "ConstantBuffers.h"
#include "VertexShader.h"

class UIImage : public UIBase
{
public:
	UIImage(Graphics& gfx);
	UIImage(Graphics& gfx, const std::wstring& texPath);

	void draw(Graphics& gfx) noexcept override;

	void setFillAmount(float value);
	void setFillType(FillType fillType) noexcept;
	float getFillAmount() const noexcept;

private:
	struct CBVS
	{
		XMMATRIX World;
		float FillAmount;
		XMFLOAT3 pad;
	};

	std::unique_ptr <VertexShader> mVS;
	std::unique_ptr<VertexConstantBuffer<CBVS>> mVCB;
	float mFillAmount;
};

