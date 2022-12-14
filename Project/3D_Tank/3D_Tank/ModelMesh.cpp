#include "ModelMesh.h"
#include "BindableBase.h"

ModelMesh::ModelMesh(RenderComponent * owner, const std::string vertex, const std::wstring& texture)
	:Mesh(owner)
{
	Graphics& gfx = RenderManager::sGetInstance()->getGraphics();
	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getModel(mesh, vertex);
	addBind(std::make_unique<VertexBuffer>(gfx, mesh.vertices));

	auto pvs = std::make_unique<VertexShader>(gfx, L"Light_VS.cso");
	auto pvsbc = pvs->getBytecode();
	addBind(std::move(pvs));

	addBind(std::make_unique<PixelShader>(gfx, L"Light_PS.cso"));

	addIndexBuffer(std::make_unique<IndexBuffer>(gfx, mesh.indices));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	addBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	addBind(std::make_unique<Texture>(gfx, texture.c_str()));

	addBind(std::make_unique<Sampler>(gfx));
	
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.FrontCounterClockwise = false;
	rd.DepthClipEnable = true;
	addBind(std::make_unique<Rasterizer>(gfx, rd));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_unique<TransferCbuf>(gfx, *this));

	addBind(std::make_unique<TransferCbuf>(gfx, *this));

	addBind(std::make_unique<PSTransCBuf>(gfx, *this));

	addBind(std::make_unique<GeometryShader>());

	addBind(std::make_unique<Rasterizer>(gfx));

	initMaterial();
}

ModelMesh::ModelMesh(RenderComponent * owner, const std::string vertex, const std::wstring & texture, DirectX::XMVECTOR & maxPoint, DirectX::XMVECTOR & minPoint)
	:Mesh(owner)
{
	Graphics& gfx = RenderManager::sGetInstance()->getGraphics();
	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getModel(mesh, vertex, maxPoint, minPoint);
	addBind(std::make_unique<VertexBuffer>(gfx, mesh.vertices));

	auto pvs = std::make_unique<VertexShader>(gfx, L"Light_VS.cso");
	auto pvsbc = pvs->getBytecode();
	addBind(std::move(pvs));

	addBind(std::make_unique<PixelShader>(gfx, L"Light_PS.cso"));

	addIndexBuffer(std::make_unique<IndexBuffer>(gfx, mesh.indices));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	addBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	addBind(std::make_unique<Texture>(gfx, texture.c_str()));

	addBind(std::make_unique<Sampler>(gfx));

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.FrontCounterClockwise = false;
	rd.DepthClipEnable = true;
	addBind(std::make_unique<Rasterizer>(gfx, rd));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_unique<TransferCbuf>(gfx, *this));

	addBind(std::make_unique<PSTransCBuf>(gfx, *this));

	addBind(std::make_unique<GeometryShader>());

	initMaterial();
}