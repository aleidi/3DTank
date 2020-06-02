#pragma once
#include "GameObjectFactory.h"

class SphereObjectFactory : public GameObjectFactory {
public:
	SphereObjectFactory();
	~SphereObjectFactory();
	GameObject* getObject();

private:

};

