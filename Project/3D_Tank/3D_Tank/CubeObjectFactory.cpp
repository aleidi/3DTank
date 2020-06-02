#include "CubeObjectFactory.h"

CubeObjectFactory::CubeObjectFactory() {
}

CubeObjectFactory::~CubeObjectFactory() {
}

GameObject* CubeObjectFactory::getObject() {
	Transform* trans = new Transform();
	GameObject* obj = new GameObject(trans);
	// obj->addComponent(trans);
	return obj;
}