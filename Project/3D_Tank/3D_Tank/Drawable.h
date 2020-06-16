#pragma once
#include "Graphics.h"
#include "Bindable.h"
#include "LightHelper.h"

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual DirectX::XMMATRIX getTransformXM() const noexcept = 0;
	virtual void draw(Graphics& gfx) noexcept;
	virtual void onUpdate(float deltaTime) noexcept = 0;
	virtual void initMaterial() noexcept;
	virtual Material getMaterial() const;
	void addBind(std::unique_ptr<Bindable> bind) noexcept;
	void addIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf) noexcept;
	virtual ~Drawable() = default;
protected:
	const IndexBuffer* pIndexBuffer = nullptr;
	std::list<std::unique_ptr<Bindable>> mBinds;
	Material mMaterial;
};