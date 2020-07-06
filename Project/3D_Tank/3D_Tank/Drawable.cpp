#include "Drawable.h"
#include "IndexBuffer.h"
#include <cassert>
#include <typeinfo>

void Drawable::draw(Graphics& gfx) noexcept
{
	if (!mCanDraw)
	{
		return;
	}
	for (auto& b : mBinds)
	{
		b->bind(gfx);
	}
	gfx.DrawIndexed(pIndexBuffer->getCount());
}

void Drawable::initMaterial() noexcept
{
	mMaterial.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mMaterial.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mMaterial.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);
	mMaterial.Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
}

Material Drawable::getMaterial() const
{
	return mMaterial;
}

void Drawable::setMaterial(Material mat)
{
	mMaterial = mat;
}

void Drawable::addBind(std::unique_ptr<Bindable> bind) noexcept
{
	assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
	mBinds.push_back(std::move(bind));
}

void Drawable::addIndexBuffer(std::unique_ptr<IndexBuffer> ibuf) noexcept
{
	assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);
	pIndexBuffer = ibuf.get();
	mBinds.push_back(std::move(ibuf));
}

void Drawable::enableDraw(bool value)
{
	mCanDraw = value;
}

void Drawable::setBlend(Graphics & gfx, const D3D11_BLEND_DESC & bd)
{
	Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState;
	gfx.getDevice()->CreateBlendState(&bd, pBlendState.GetAddressOf());
	gfx.getContext()->OMSetBlendState(pBlendState.Get(), nullptr, 0xFFFFFFFF);
}