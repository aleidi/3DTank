#include "CubeObjectFactory.h"
#include "ComponentBase.h"
#include "MeshBase.h"

CubeObjectFactory::CubeObjectFactory() {
}

CubeObjectFactory::~CubeObjectFactory() {
}

GameObject* CubeObjectFactory::getObject() {
	//create gameobject
	GameObject* obj = new GameObject();

	//create render component
	RenderComponent* rc = new RenderComponent(obj);
	Cube* cube = new Cube(rc);
	rc->setMesh(cube);
	//attach render component to gameobject
	obj->addComponent(rc);

	return obj;
}