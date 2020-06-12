#pragma once
#include "Drawable.h"

class RenderComponent;

class Mesh : public Drawable
{
public:
	Mesh() = delete;
	Mesh(RenderComponent* owner);
	virtual void onUpdate(float deltaTime) noexcept override;
	virtual DirectX::XMMATRIX getTransformXM() const noexcept override;
	virtual ~Mesh();
private:
	RenderComponent* mOwner;
};