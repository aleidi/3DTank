#pragma once
#include <DirectXMath.h>
#include "Component.h"

class Mesh;

class RenderComponent : public Component
{
public:
	RenderComponent(GameObject* obj):RenderComponent(obj,nullptr) {}
	RenderComponent(GameObject* obj, Mesh* theMesh);
	~RenderComponent();

	void addMesh(Mesh* theMesh) noexcept;
	DirectX::XMMATRIX getTransformXM() noexcept;

private:
	Mesh* mMesh;
};

