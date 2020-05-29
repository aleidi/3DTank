#include "RenderComponent.h"
#include "Rendering.h"

RenderComponent::RenderComponent(Drawable3D* theMesh)
	:mMesh(theMesh)
{
	mManager->addDrawable3D(mMesh);
}

RenderComponent::~RenderComponent()
{
	mManager->removeDrawable3D(mMesh);
}