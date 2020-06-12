#include "Plane.h"
#include "BindableBase.h"

Plane::Plane(RenderComponent * owner)
	:Mesh(owner)
{
	Graphics& gfx = RenderManager::sGetInstance()->getGraphics();
	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getPlane(mesh);
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

	addBind(std::make_unique<Rasterizer>(gfx));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_unique<TransferCbuf>(gfx, *this));
}
