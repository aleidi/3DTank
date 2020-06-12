#pragma once
#include <DirectXMath.h>

#include "Component.h"
#include "LightHelper.h"

class Mesh;

class RenderComponent : public Component
{
public:
	RenderComponent(GameObject* obj);
	~RenderComponent();

	void setMesh(Mesh* theMesh) noexcept;
	DirectX::XMMATRIX getWorldMatrix() noexcept;
	Material getMaterial() const noexcept;
	void setMaterial(const Material& mat) noexcept;

private:
	Mesh* mMesh;
	Material mMaterial;
};

