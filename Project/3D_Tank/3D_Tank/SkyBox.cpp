#include "SkyBox.h"
#include "BindableBase.h"

SkyBox::SkyBox(Graphics & gfx)
{
	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getSphere(mesh);

	AddBind(std::make_unique<VertexBuffer>(gfx, mesh.vertices));

	auto pvs = std::make_unique<VertexShader>(gfx, L"SkyBox_VS.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	AddBind(std::make_unique<PixelShader>(gfx, L"SkyBox_PS.cso"));

	AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, mesh.indices));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	AddBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	AddBind(std::make_unique<Texture>(gfx, L"Skybox\\Sand"));

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	AddBind(std::make_unique<Sampler>(gfx, sampDesc));

	D3D11_DEPTH_STENCIL_DESC dd;
	dd.DepthEnable = true;
	dd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dd.StencilEnable = false;
	AddBind(std::make_unique<DepthStencil>(gfx,dd));

	AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}

void SkyBox::Update(float deltaTime) noexcept
{
}

DirectX::XMMATRIX SkyBox::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixTranslation(mPosX, mPosY, mPosZ);
}

void SkyBox::setPosition(float x, float y, float z)
{
	mPosX = x;
	mPosY = y;
	mPosZ = z;
}
