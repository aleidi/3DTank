#include "TestCube.h"
#include "BindableBase.h"

TestCube::TestCube(Graphics & gfx, UINT id)
	:
	pos({ 0.0f,0.0f,0.0f }), rot({ 0.0f,0.0f,0.0f }), scale({ 1.0f,1.0f,1.0f })
{
	mID = id;

	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getCube(mesh);
	AddBind(std::make_unique<VertexBuffer>(gfx, mesh.vertices));

	auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShaderTex.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	AddBind(std::make_unique<PixelShader>(gfx, L"PixelShaderTex.cso"));

	AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, mesh.indices));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	AddBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	AddBind(std::make_unique<Texture>(gfx, L"Resource\\Objects\\TX_FreightContainer_01a_ALB.dds"));

	AddBind(std::make_unique<Sampler>(gfx));

	AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}

TestCube::~TestCube()
{
}

void TestCube::Update(float deltaTime) noexcept
{
	
}

DirectX::XMMATRIX TestCube::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
		DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z) *
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 10.0f);
}

void TestCube::Translate(float x, float y, float z)
{
	const float deg2rad = XM_PI / 180;
	pos.x += x * deg2rad;
	pos.y += y * deg2rad;
	pos.z += z * deg2rad;
}

void TestCube::Rotate(float pitch, float yaw, float roll)
{
	rot.x += pitch;
	rot.y += yaw;
	rot.z += roll;
}

void TestCube::Scale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}
