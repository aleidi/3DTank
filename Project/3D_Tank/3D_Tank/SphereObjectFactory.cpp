#include "SphereObjectFactory.h"

SphereObjectFactory::SphereObjectFactory() {
}

SphereObjectFactory::~SphereObjectFactory() {
}

GameObject* SphereObjectFactory::getObject() {
	Transform* trans = new Transform();
	GameObject* obj = new GameObject(trans);
	// obj->addComponent(trans);
	return obj;
}