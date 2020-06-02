#include "CubeObjectFactory.h"

CubeObjectFactory::CubeObjectFactory() {
}

CubeObjectFactory::~CubeObjectFactory() {
}

GameObject* CubeObjectFactory::getObject() {
	GameObject* obj = new GameObject();
	Transform* trans = new Transform();
	// obj->addComponent(trans);
	return obj;
}