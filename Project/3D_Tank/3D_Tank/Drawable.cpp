#include "Drawable.h"
#include "IndexBuffer.h"
#include <cassert>
#include <typeinfo>

void Drawable::draw(Graphics& gfx) const noexcept
{
	for (auto& b : mBinds)
	{
		b->bind(gfx);
	}
	gfx.DrawIndexed(pIndexBuffer->getCount());
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