#pragma once
#include "Component.h"
#include "EnginePlat.h"
#include "Drawable.h"

class Mesh : public Component
{
public:
	Mesh();
	~Mesh();

protected:
	std::unique_ptr<Drawable> shape;
};

