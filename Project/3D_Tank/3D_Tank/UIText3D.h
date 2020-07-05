#pragma once
#include "UIText.h"

class UIText3D : public UIText
{
public:
	UIText3D() = default;
	UIText3D(Graphics& gfx);
	UIText3D(Graphics& gfx, std::wstring text);
	DirectX::XMMATRIX getTransformXM() const noexcept override;
	void draw(Graphics& gfx) noexcept override;
	void setInterval(float value);
	void setSizeScale(float x, float y);
	
protected:
	void renderTarget(Graphics& gfx);
	void initRenderTarget(Graphics& gfx);

protected:
	float mInterval;
	float mSizeFactorX;
	float mSizeFactorY;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pSRVRT;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRTCashe;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSVCashe;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pRenderTargetTextureMap;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetViewMap;
	UIText* mText2D;
};

