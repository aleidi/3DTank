#include "CubeObjectFactory.h"

CubeObjectFactory::CubeObjectFactory() {
}

CubeObjectFactory::~CubeObjectFactory() {
}

GameObject* CubeObjectFactory::getObject() {
	GameObject* obj = new GameObject();
	return obj;
}