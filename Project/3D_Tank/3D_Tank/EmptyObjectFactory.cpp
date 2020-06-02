#include "EmptyObjectFactory.h"

EmptyObjectFactory::EmptyObjectFactory() {
}

EmptyObjectFactory::~EmptyObjectFactory() {
}

GameObject* EmptyObjectFactory::getObject() {
	GameObject* obj = new GameObject();
	return obj;
}