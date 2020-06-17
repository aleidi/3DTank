#include "ComponentFactory.h"
#include "ComponentBase.h"
#include "GeometryGenerator.h"
#include "MeshBase.h"
#include "RenderComponent.h"

RenderComponent* ComponentFactory::createModel(GameObject & obj, const std::string & modelPath, const std::wstring & texturePath)
{
	RenderComponent* rc = new RenderComponent(&obj);
	rc->setMesh(new ModelMesh(rc, modelPath, texturePath));
	obj.addComponent(rc);
	return rc;
}

RenderComponent* ComponentFactory::createModel(GameObject & obj, const std::string & modelPath, const std::wstring & texturePath, DirectX::XMVECTOR & maxPoint, DirectX::XMVECTOR & minPoint)
{
	RenderComponent* rc = new RenderComponent(&obj);
	rc->setMesh(new ModelMesh(rc, modelPath, texturePath, maxPoint, minPoint));
	obj.addComponent(rc);
	return rc;
}