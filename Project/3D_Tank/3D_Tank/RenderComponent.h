#pragma once
#include <DirectXMath.h>
#include "Component.h"

class Mesh;

class RenderComponent : public Component
{
public:
	RenderComponent(GameObject* obj);
	~RenderComponent();

	void setMesh(Mesh* theMesh) noexcept;
	DirectX::XMMATRIX getWorldMatrix() noexcept;

private:
	Mesh* mMesh;
};

