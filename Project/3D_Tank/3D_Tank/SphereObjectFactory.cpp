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
	Sphere* sphere = new Sphere(rc);
	rc->setMesh(sphere);
	//attach render component to gameobject
	obj->addComponent(rc);

	return obj;
}