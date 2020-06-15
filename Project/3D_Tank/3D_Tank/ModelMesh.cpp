#include "ModelMesh.h"
#include "BindableBase.h"

ModelMesh::ModelMesh(RenderComponent * owner, const std::string vertex, const std::wstring& texture)
	:Mesh(owner)
{
	Graphics& gfx = RenderManager::sGetInstance()->getGraphics();
	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getModel(mesh, vertex);
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

	AddBind(std::make_unique<Texture>(gfx, texture.c_str()));

	AddBind(std::make_unique<Sampler>(gfx));

	AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}

ModelMesh::ModelMesh(RenderComponent * owner, const std::string vertex, const std::wstring & texture, DirectX::XMVECTOR & maxPoint, DirectX::XMVECTOR & minPoint)
	:Mesh(owner)
{
	Graphics& gfx = RenderManager::sGetInstance()->getGraphics();
	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getModel(mesh, vertex, maxPoint, minPoint);
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

	AddBind(std::make_unique<Texture>(gfx, texture.c_str()));

	AddBind(std::make_unique<Sampler>(gfx));

	AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}

ModelMesh::ModelMesh(RenderComponent * owner, const std::string vertex, const std::wstring & texture, D3D11_SAMPLER_DESC sampDesc)
	:Mesh(owner)
{
	Graphics& gfx = RenderManager::sGetInstance()->getGraphics();
	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getModel(mesh, vertex);
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

	AddBind(std::make_unique<Texture>(gfx, texture.c_str()));

	AddBind(std::make_unique<Sampler>(gfx, sampDesc));

	AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}
