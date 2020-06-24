#pragma once
#include "Mesh.h"

class Sphere : public Mesh
{
public:
	Sphere(RenderComponent* owner);
	Sphere(RenderComponent* owner, const std::wstring& texture);
};

