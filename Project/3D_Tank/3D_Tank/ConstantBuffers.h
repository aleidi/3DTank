#pragma once
#include "Bindable.h"

template<typename C>
class ConstantBuffers : public Bindable
{
public:
	ConstantBuffers(Graphics& gfx, const C& consts)
	{
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(consts);
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &consts;
		getDevice(gfx)->CreateBuffer(&cbd, &csd, &pConstantBuffer);
	}

	ConstantBuffers(Graphics& gfx)
	{
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(C);
		cbd.StructureByteStride = 0u;
		getDevice(gfx)->CreateBuffer(&cbd, nullptr, &pConstantBuffer);
	}

	void onUpdate(Graphics& gfx, const C& consts)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		getContext(gfx)->Map(
			pConstantBuffer.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,
			&msr
		);
		memcpy(msr.pData, &consts, sizeof(consts));
		getContext(gfx)->Unmap(pConstantBuffer.Get(), 0u);
	}

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffers<C>
{
	using ConstantBuffers<C>::pConstantBuffer;
	using Bindable::getContext;
public:
	using ConstantBuffers<C>::ConstantBuffers;
	void bind(Graphics& gfx) noexcept override
	{
		getContext(gfx)->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffers<C>
{
	using ConstantBuffers<C>::pConstantBuffer;
	using Bindable::getContext;
public:
	using ConstantBuffers<C>::ConstantBuffers;
	void bind(Graphics& gfx) noexcept override
	{
		getContext(gfx)->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};