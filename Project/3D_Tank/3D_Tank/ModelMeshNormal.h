#pragma once
#include "Mesh.h"

class ModelMeshNormal : public Mesh
{
public:
	ModelMeshNormal(RenderComponent * owner, const std::string vertex, const std::wstring& texture);
};

