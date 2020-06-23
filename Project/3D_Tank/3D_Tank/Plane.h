#pragma once
#include "Mesh.h"

class Plane : public Mesh
{
public:
	Plane(RenderComponent* owner);
	Plane(RenderComponent* owner, const std::wstring& texture);
};

