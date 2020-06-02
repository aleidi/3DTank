#pragma once
#include "GameObjectFactory.h"

class PlaneObjectFactory : public GameObjectFactory
{
public:
	PlaneObjectFactory();
	~PlaneObjectFactory();
	GameObject* getObject() override;
};

