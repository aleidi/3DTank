#pragma once
#include "UIImage.h"

class GeometryShader;

class UIImage3D : public UIImage
{
public:
	UIImage3D(Graphics& gfx);
	UIImage3D(Graphics& gfx, const std::wstring& texPath);
	void draw(Graphics& gfx) noexcept override;
	void setFillType(FillType fillType) noexcept override;

private:
	struct CBGS
	{
		XMMATRIX View;
		XMMATRIX Proj;
		XMFLOAT4 EyePosW;
		XMFLOAT3 WorldPos;
		float FillAmount;
		XMFLOAT2 Size;
	};

	struct VertexPosSize
	{
		XMFLOAT2 Size;
	};

	std::unique_ptr<GeometryConstantBuffer<CBGS>> mGSCBuf;
	std::unique_ptr<GeometryShader> mGS;

};

