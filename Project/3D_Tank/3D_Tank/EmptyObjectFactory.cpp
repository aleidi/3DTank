#include "EmptyObjectFactory.h"

EmptyObjectFactory::EmptyObjectFactory() {
}

EmptyObjectFactory::~EmptyObjectFactory() {
}

GameObject* EmptyObjectFactory::getObject() {
	Transform* trans = new Transform();
	GameObject* obj = new GameObject(trans);
	// obj->addComponent(trans);
	return obj;
}