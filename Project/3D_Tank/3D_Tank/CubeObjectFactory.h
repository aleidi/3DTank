#pragma once
#include "GameObjectFactory.h"

class CubeObjectFactory : public GameObjectFactory {
public:
	CubeObjectFactory();
	~CubeObjectFactory();
	GameObject* getObject() override;
};

