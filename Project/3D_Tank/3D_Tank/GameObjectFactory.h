#pragma once
#include "GameObject.h"

class GameObjectFactory {
public:
	GameObjectFactory(){}
	virtual ~GameObjectFactory(){}
	virtual GameObject* getObject() = 0;
};

