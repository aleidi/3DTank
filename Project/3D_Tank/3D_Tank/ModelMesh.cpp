#include "ModelMesh.h"
#include "BindableBase.h"

ModelMesh::ModelMesh(Graphics & gfx)
	:
	pos({ 0.0f,0.0f,0.0f }), rot({ 0.0f,0.0f,0.0f }), scale({ 0.1f,0.1f,0.1f })
{
	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getModel(mesh,"Tank\\TankBattery.txt");
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

	AddBind(std::make_unique<Texture>(gfx, L"Resource\\Model\\Tank\\TankTex.dds"));

	AddBind(std::make_unique<Sampler>(gfx));

	AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}

ModelMesh::~ModelMesh()
{
}

void ModelMesh::Update(float deltaTime) noexcept
{
}

DirectX::XMMATRIX ModelMesh::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
		DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z) *
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 10.0f);
}

void ModelMesh::Translate(float x, float y, float z)
{
}

void ModelMesh::Rotate(float pitch, float yaw, float roll)
{
}

void ModelMesh::Scale(float x, float y, float z)
{
}
