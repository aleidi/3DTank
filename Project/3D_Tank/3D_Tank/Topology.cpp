#include "Topology.h"

Topology::Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY mType)
	:
	mType(mType)
{}

void Topology::bind(Graphics& gfx) noexcept
{
	getContext(gfx)->IASetPrimitiveTopology(mType);
}