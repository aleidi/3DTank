#pragma once
#include "GameObject.h"
#include "Transform.h"

class GameObjectFactory {
public:
	GameObjectFactory();
	~GameObjectFactory();
	virtual GameObject* getObject() = 0;

private:

};

