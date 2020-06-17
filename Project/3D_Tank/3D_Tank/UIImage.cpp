#include "UIImage.h"
#include "BindableBase.h"

UIImage::UIImage(Graphics& gfx)
	:UIImage(gfx,L"")
{}

UIImage::UIImage(Graphics & gfx, const std::wstring & texPath)
	:mFillAmount(1.0f)
{
	mWidth = 100.0f;
	mHeight = 100.0f;
	mX = 0.0f;
	mY = 0.0f;

	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getUIPanel(mesh);

	addBind(std::make_unique<VertexBuffer>(gfx, mesh.vertices, true));

	std::vector<std::wstring> vsPathes;
	vsPathes.push_back(L"UIVSHorizontalL.cso");
	vsPathes.push_back(L"UIVSHorizontalR.cso");
	vsPathes.push_back(L"UIVSVerticalT.cso");
	vsPathes.push_back(L"UIVSVerticalB.cso");
	mVS = std::make_unique<VertexShader>(gfx, vsPathes);
	auto pvsbc = mVS->getBytecode();

	addBind(std::make_unique<PixelShader>(gfx, L"UIPixelShader.cso"));

	addIndexBuffer(std::make_unique<IndexBuffer>(gfx, mesh.indices));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	addBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	addBind(std::make_unique<Texture>(gfx, texPath));

	addBind(std::make_unique<Sampler>(gfx));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	mVCB = std::make_unique<VertexConstantBuffer<CBVS>>(gfx);
}

void UIImage::draw(Graphics& gfx) noexcept
{
	if (mIsEnable != true)
	{
		return;
	}

	mVCB->onUpdate(gfx,
		{
			DirectX::XMMatrixTranspose(getTransformXM()),
			getFillAmount()
		}
	);

	for (auto& b : mBinds)
	{
		b->bind(gfx);
	}
	mVCB->bind(gfx);
	mVS->bind(gfx);
	gfx.DrawIndexed(pIndexBuffer->getCount());
}

void UIImage::setFillAmount(float value)
{
	mFillAmount = value;
}

void UIImage::setFillType(FillType fillType) noexcept
{
	switch (fillType.Method)
	{
	case FillMethod::Horizontal:
		if (fillType.Origin == FillOrigin::Left)
		{
			mVS->changeShader(0);
		}
		else if (fillType.Origin == FillOrigin::Right)
		{
			mVS->changeShader(1);
		}
		break;

	case FillMethod::Vertical:
		if (fillType.Origin == FillOrigin::Top)
		{
			mVS->changeShader(2);
		}
		else if (fillType.Origin == FillOrigin::Bottom)
		{
			mVS->changeShader(3);
		}
		break;

	default:
		mVS->changeShader(0);
		break;
	}

}

float UIImage::getFillAmount() const noexcept
{
	return mFillAmount;
}
