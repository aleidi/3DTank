#include "RenderComponent.h"
#include "Rendering.h"
#include "Drawable3D.h"

RenderComponent::RenderComponent(Drawable3D* theMesh,Rendering* theRender)
	:mMesh(theMesh),mRender(theRender)
{
}

RenderComponent::~RenderComponent()
{
}