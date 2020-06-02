#include "EmptyObjectFactory.h"

EmptyObjectFactory::EmptyObjectFactory() {
}

EmptyObjectFactory::~EmptyObjectFactory() {
}

GameObject* EmptyObjectFactory::getObject() {
	GameObject* obj = new GameObject();
	Transform* trans = new Transform();
	// obj->addComponent(trans);
	return obj;
}