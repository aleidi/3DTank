#include "PlaneObjectFactory.h"
#include "ComponentBase.h"
#include "MeshBase.h"

PlaneObjectFactory::PlaneObjectFactory()
{
}

PlaneObjectFactory::~PlaneObjectFactory()
{
}

GameObject * PlaneObjectFactory::getObject()
{
	//create gameobject
	GameObject* obj = new GameObject();

	//create render component
	RenderComponent* rc = new RenderComponent(obj);
	Plane* plane = new Plane(rc);
	rc->setMesh(plane);
	//attach render component to gameobject
	obj->addComponent(rc);

	return obj;
}
