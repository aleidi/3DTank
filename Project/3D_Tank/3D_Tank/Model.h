#pragma once
#include "Component.h"
#include "EngineCommon.h"
#include "Drawable.h"

class Model : public Component
{
public:
	Model();
	~Model();

protected:
	std::unique_ptr<Drawable> shape;
};

