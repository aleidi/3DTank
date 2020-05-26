#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics& gfx, const std::vector<UINT>& indices)
	:
	mCount(indices.size())
{
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = mCount * sizeof(UINT);
	ibd.StructureByteStride = sizeof(UINT);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices.data();
	GetDevice(gfx)->CreateBuffer(&ibd, &isd, &pIndexBuffer);
}

void IndexBuffer::bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
}

UINT IndexBuffer::getCount() const noexcept
{
	return mCount;
}