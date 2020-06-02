#pragma once
#include "GameObjectFactory.h"

class EmptyObjectFactory : public GameObjectFactory {
public:
	EmptyObjectFactory();
	~EmptyObjectFactory();
	GameObject* getObject() override;

private:

};

