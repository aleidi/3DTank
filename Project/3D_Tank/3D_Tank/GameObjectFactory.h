#pragma once
#include "GameObject.h"

class GameObjectFactory {
public:
	GameObjectFactory();
	~GameObjectFactory();
	virtual GameObject *getObject();

private:

};

