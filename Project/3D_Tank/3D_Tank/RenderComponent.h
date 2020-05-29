#pragma once
#include "Component.h"

class Drawable3D;
class Rendering;

class RenderComponent : public Component
{
public:
	RenderComponent(Drawable3D* theMesh);
	~RenderComponent();
private:
	Drawable3D* mMesh;
	Rendering* mManager;
};

