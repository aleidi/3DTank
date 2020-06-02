#pragma once
#include "Component.h"

class Mesh;

class RenderComponent : public Component
{
public:
	RenderComponent():RenderComponent(nullptr) {}
	RenderComponent(Mesh* theMesh);
	~RenderComponent();

	void addMesh(Mesh* theMesh) noexcept;

private:
	Mesh* mMesh;
};

