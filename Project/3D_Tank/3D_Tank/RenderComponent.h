#pragma once
#include "Component.h"

class Drawable3D;
class Rendering;

class RenderComponent : public Component
{
public:
	RenderComponent(Drawable3D* theMesh,Rendering* theRender);
	~RenderComponent();

private:
	Drawable3D* mMesh;
	Rendering*  mRender;
};

