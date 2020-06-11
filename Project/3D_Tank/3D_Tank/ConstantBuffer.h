#pragma once
#include "Bindable.h"

class ConstantBuffer : public Bindable
{
public:
	template<typename C>
	ConstantBuffer(Graphics& gfx, const C& buffer)
	{
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(buffer);
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &buffer;
		GetDevice(gfx)->CreateBuffer(&cbd, &csd, &pConstantBuffer);
	}

	template<typename C>
	void Update(Graphics& gfx, const C& consts)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetContext(gfx)->Map(
			pConstantBuffer.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,
			&msr
		);
		memcpy(msr.pData, &consts, sizeof(consts));
		GetContext(gfx)->Unmap(pConstantBuffer.Get(), 0u);
	}

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
};

class VertexConstantBuffer : public ConstantBuffer
{
public:
	template<typename C>
	VertexConstantBuffer(Graphics& gfx, const C& buffer)
		:ConstantBuffer(gfx, buffer) 
	{}

	void bind(Graphics& gfx) noexcept override
	{
		GetContext(gfx)->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};

class PixelConstantBuffer : public ConstantBuffer
{
public:
	template<typename C>
	PixelConstantBuffer(Graphics& gfx, const C& buffer)
		:ConstantBuffer(gfx, buffer)
	{}

	void bind(Graphics& gfx) noexcept override
	{
		GetContext(gfx)->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};