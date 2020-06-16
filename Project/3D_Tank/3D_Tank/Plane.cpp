#include "Plane.h"
#include "BindableBase.h"

Plane::Plane(RenderComponent * owner)
	:Mesh(owner)
{
	Graphics& gfx = RenderManager::sGetInstance()->getGraphics();
	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getPlane(mesh);
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

	addBind(std::make_unique<Texture>(gfx, L"Objects/DefaultTexture"));

	addBind(std::make_unique<Sampler>(gfx));

	addBind(std::make_unique<Rasterizer>(gfx));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_unique<TransferCbuf>(gfx, *this));

	addBind(std::make_unique<PSTransCBuf>(gfx, *this));

	initMaterial();
}
