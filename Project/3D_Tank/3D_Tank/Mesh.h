#pragma once
#include "Drawable.h"

class RenderComponent;

class Mesh : public Drawable
{
public:
	Mesh() = delete;
	Mesh(RenderComponent* owner);
	virtual ~Mesh();

	virtual void onUpdate(float deltaTime) noexcept override;
	virtual DirectX::XMMATRIX getTransformXM() const noexcept override;
	virtual Material getMaterial() const noexcept override;
private:
	RenderComponent* mOwner;
};