#pragma once
#include "Drawable.h"

class RenderComponent;

class Mesh : public Drawable
{
public:
	Mesh() = default;
	Mesh(RenderComponent* owner, Graphics& gfx);
	virtual void Update(float deltaTime) noexcept override;
	virtual DirectX::XMMATRIX GetTransformXM() const noexcept override;
	virtual ~Mesh();
private:
	RenderComponent* mOwner;
};

