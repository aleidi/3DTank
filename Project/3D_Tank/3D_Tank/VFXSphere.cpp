#include "VFXSphere.h"
#include "BindableBase.h"

VFXSphere::VFXSphere(Graphics& gfx)
	:mX(0.0f),mY(0.0f),mZ(0.0f),mPitch(0.0f),mYaw(0.0f),mRoll(0.0f),
	mTileOffsetX(0.0f),mTileOffsetY(0.0f)
{
	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getSphere(mesh);

	addBind(std::make_unique<VertexBuffer>(gfx, mesh.vertices,true));

	auto pvs = std::make_unique<VertexShader>(gfx, L"VFXSphere_VS.cso");
	auto pvsbc = pvs->getBytecode();
	addBind(std::move(pvs));

	addBind(std::make_unique<PixelShader>(gfx, L"VFXSphere_PS.cso"));

	addIndexBuffer(std::make_unique<IndexBuffer>(gfx, mesh.indices));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	addBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	addBind(std::make_unique<Texture>(gfx, L"VFX/Twist2", 0));

	addBind(std::make_unique<Texture>(gfx, L"VFX/Twist1", 1));

	addBind(std::make_unique<Sampler>(gfx));

	addBind(std::make_unique<DepthStencil>(gfx));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	mVCB = std::make_unique<VertexConstantBuffer<CBVS>>(gfx);

	addBind(std::make_unique<GeometryShader>());

	mMaterial.Color = XMFLOAT4(0.86f, 0.078f, 0.235f, 1.0f);
	mPCB = std::make_unique<PixelConstantBuffer<XMFLOAT4>>(gfx, mMaterial.Color);
}

void VFXSphere::onUpdate(float deltaTime) noexcept
{

}

DirectX::XMMATRIX VFXSphere::getTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(mPitch, mYaw, mRoll) *
		DirectX::XMMatrixTranslation(mX, mY, mZ);
}

void VFXSphere::tileOffset(float x, float y)
{
	mTileOffsetX += x;
	mTileOffsetY += y;
}

void VFXSphere::setPosition(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}

void VFXSphere::translate(float x, float y, float z)
{
	mX += x;
	mY += y;
	mZ += z;
}

void VFXSphere::rotate(float pitch, float yaw, float roll)
{
	mPitch += pitch;
	mYaw += yaw;
	mRoll += roll;
}

void VFXSphere::setRotation(float pitch, float yaw, float roll)
{
	mPitch = pitch;
	mYaw = yaw;
	mRoll = roll;
}

void VFXSphere::draw(Graphics& gfx) noexcept
{
	mVCB->onUpdate(gfx,
		{
			DirectX::XMMatrixTranspose(getTransformXM()),
			DirectX::XMMatrixTranspose(gfx.getView()),
			DirectX::XMMatrixTranspose(gfx.getProj()),
			XMFLOAT2(mTileOffsetX,mTileOffsetY)
		}
	);

	mPCB->onUpdate(gfx, mMaterial.Color);

	for (auto& b : mBinds)
	{
		b->bind(gfx);
	}
	mVCB->bind(gfx);
	mPCB->bind(gfx);
	SetBlendTransparent(gfx);
	gfx.DrawIndexed(pIndexBuffer->getCount());
	ResetBlendState(gfx);
}

void VFXSphere::SetBlendTransparent(Graphics& gfx)
{
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	setBlend(gfx, bd);
}

void VFXSphere::ResetBlendState(Graphics& gfx)
{
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	setBlend(gfx, bd);
}
