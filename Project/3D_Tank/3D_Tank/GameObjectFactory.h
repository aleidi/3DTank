#pragma once
#include "GameObject.h"
#include "Transform.h"

class GameObjectFactory {
public:
	GameObjectFactory(){}
	virtual ~GameObjectFactory(){}
	virtual GameObject* getObject() = 0;

private:

};

