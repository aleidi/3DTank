#pragma once
#include "Mesh.h"

class Cube : public Mesh
{
public:
	Cube(RenderComponent* owner);
	Cube(RenderComponent* owner, const std::wstring& texture);
};

