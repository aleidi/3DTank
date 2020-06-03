#pragma once
#include "Mesh.h"

class ModelMesh : public Mesh
{
public:
	ModelMesh(RenderComponent * owner, const std::string vertex, const std::wstring& texture);
};

