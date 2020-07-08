#include "UIImage3D.h"
#include "BindableBase.h"

UIImage3D::UIImage3D(Graphics& gfx)
	:UIImage3D(gfx,L"")
{
}

UIImage3D::UIImage3D(Graphics & gfx, const std::wstring & texPath)
{
	mFillAmount = 1.0f;

	mWidth = 1.0f;
	mHeight = 1.0f;
	mX = 0.0f;
	mY = 0.0f;
	mZ = 10.0f;

	std::vector<VertexPosSize> vertice;
	VertexPosSize point;
	point.Size = XMFLOAT2(10, 10);
	vertice.push_back(point);

	addBind(std::make_unique<VertexBuffer>(gfx, vertice));

	auto pvs = std::make_unique<VertexShader>(gfx, L"Billboard_VS.cso");
	auto pvsbc = pvs->getBytecode();
	addBind(std::move(pvs));

	std::vector<std::wstring> vsPathes;
	vsPathes.push_back(L"UI3DGSHorizontalL.cso");
	vsPathes.push_back(L"UI3DGSHorizontalR.cso");
	vsPathes.push_back(L"UI3DGSVerticalT.cso");
	vsPathes.push_back(L"UI3DGSVerticalB.cso");
	mGS = std::make_unique<GeometryShader>(gfx, vsPathes);

	addBind(std::make_unique<PixelShader>(gfx, L"Billboard_PS.cso"));


	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "SIZE",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	addBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	addBind(std::make_unique<Texture>(gfx, texPath));

	addBind(std::make_unique<Sampler>(gfx));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_POINTLIST));

	mMaterial.Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mPCBuf = std::make_unique<PixelConstantBuffer<XMFLOAT4>>(gfx, mMaterial.Color);

	CBGS cbgs;
	mGSCBuf = std::make_unique<GeometryConstantBuffer<CBGS>>(gfx, cbgs);

	addBind(std::make_unique<Rasterizer>(gfx));

}

void UIImage3D::draw(Graphics& gfx) noexcept
{
	if (mIsEnable != true)
	{
		return;
	}

	mPCBuf->onUpdate(gfx, mMaterial.Color);
	XMFLOAT3 cam;
	XMStoreFloat3(&cam, gfx.getCameraPosition());
	mGSCBuf->onUpdate(gfx,
		{
			XMMatrixTranspose(gfx.getView()),
			XMMatrixTranspose(gfx.getProj()),
			XMFLOAT4(cam.x,cam.y,cam.z,1.0f),
			XMFLOAT3(mX,mY,mZ),
			mFillAmount,
			XMFLOAT2(mWidth,mHeight)
		});

	mGSCBuf->bind(gfx);
	mPCBuf->bind(gfx);
	mGS->bind(gfx);
	for (auto& b : mBinds)
	{
		b->bind(gfx);
	}
	gfx.DrawIndexed(4);
}

void UIImage3D::setFillType(FillType fillType) noexcept
{
	switch (fillType.Method)
	{
	case FillMethod::Horizontal:
		if (fillType.Origin == FillOrigin::Left)
		{
			mGS->changeShader(0);
		}
		else if (fillType.Origin == FillOrigin::Right)
		{
			mGS->changeShader(1);
		}
		break;

	case FillMethod::Vertical:
		if (fillType.Origin == FillOrigin::Top)
		{
			mGS->changeShader(2);
		}
		else if (fillType.Origin == FillOrigin::Bottom)
		{
			mGS->changeShader(3);
		}
		break;

	default:
		mGS->changeShader(0);
		break;
	}
}