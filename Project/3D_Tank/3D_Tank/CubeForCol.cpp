#include "CubeForCol.h"
#include "BindableBase.h"

CubeForCol::CubeForCol()
	:pos({ 0.0f,0.0f,0.0f }), rot({ 0.0f,0.0f,0.0f }), scale({ 1.0f,1.0f,1.0f })
{
	Graphics& gfx = RenderManager::sGetInstance()->getGraphics();
	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getCube(mesh);
	addBind(std::make_unique<VertexBuffer>(gfx, mesh.vertices));

	auto pvs = std::make_unique<VertexShader>(gfx, L"SolidVertexShader.cso");
	auto pvsbc = pvs->GetBytecode();
	addBind(std::move(pvs));

	addBind(std::make_unique<PixelShader>(gfx, L"SolidPixelShader.cso"));

	addIndexBuffer(std::make_unique<IndexBuffer>(gfx, mesh.indices));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		//{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	addBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	//addBind(std::make_unique<Texture>(gfx, L"Resource\\Model\\Objects\\TX_FreightContainer_01a_ALB.dds"));

	//addBind(std::make_unique<Sampler>(gfx));

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = false;
	addBind(std::make_unique<Rasterizer>(gfx, rd));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_unique<TransferCbuf>(gfx, *this));
}

void CubeForCol::onUpdate(float deltaTime) noexcept
{
}

DirectX::XMMATRIX CubeForCol::getTransformXM() const noexcept
{
	return DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
		DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z) *
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}

Material CubeForCol::getMaterial() const noexcept
{
	return Material();
}

void CubeForCol::Translate(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;
}

void CubeForCol::Rotate(float pitch, float yaw, float roll)
{
	const float deg2rad = XM_PI / 180;
	rot.x += pitch * deg2rad;
	rot.y += yaw * deg2rad;
	rot.z += roll * deg2rad;
}

void CubeForCol::Scale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}
