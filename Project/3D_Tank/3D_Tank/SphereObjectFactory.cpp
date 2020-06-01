#include "SphereObjectFactory.h"

SphereObjectFactory::SphereObjectFactory() {
}

SphereObjectFactory::~SphereObjectFactory() {
}

GameObject* SphereObjectFactory::getObject() {
	GameObject* obj = new GameObject();
	Transform* trans = new Transform();
	// obj->addComponent(trans);
	return obj;
}