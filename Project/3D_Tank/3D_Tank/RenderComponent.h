#pragma once
#include "Component.h"

class Drawable;
class Rendering;

class RenderComponent : public Component
{
public:
	RenderComponent(Drawable* theMesh,Rendering* theRender);
	~RenderComponent();

private:
	Drawable* mMesh;
	Rendering*  mRender;
};

