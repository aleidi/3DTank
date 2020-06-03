#include "ComponentFactory.h"
#include "ComponentBase.h"
#include "GeometryGenerator.h"
#include "MeshBase.h"

void ComponentFactory::createModel(GameObject & obj, const std::string & modelPath, const std::wstring & texturePath)
{
	RenderComponent* rc = new RenderComponent(&obj);
	rc->setMesh(new ModelMesh(rc, modelPath, texturePath));
}
