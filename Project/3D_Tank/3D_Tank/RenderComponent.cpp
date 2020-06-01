#include "RenderComponent.h"
#include "Rendering.h"

RenderComponent::RenderComponent(Drawable* theMesh,Rendering* theRender)
	:mMesh(theMesh),mRender(theRender)
{
}

RenderComponent::~RenderComponent()
{
}