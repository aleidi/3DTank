#include "SphereObjectFactory.h"
#include "ComponentBase.h"
#include "MeshBase.h"

SphereObjectFactory::SphereObjectFactory() {
}

SphereObjectFactory::~SphereObjectFactory() {
}

GameObject* SphereObjectFactory::getObject() {
	//create gameobject
	GameObject* obj = new GameObject();

	//create render component
	RenderComponent* rc = new RenderComponent(obj);
	Sphere* cube = new Sphere(rc);
	rc->setMesh(cube);
	//attach render component to gameobject
	obj->addComponent(rc);

	return obj;
}