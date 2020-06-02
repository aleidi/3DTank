#include "SphereObjectFactory.h"

SphereObjectFactory::SphereObjectFactory() {
}

SphereObjectFactory::~SphereObjectFactory() {
}

GameObject* SphereObjectFactory::getObject() {
	GameObject* obj = new GameObject();
	return obj;
}