#include "RenderComponent.h"
#include "RenderManager.h"

RenderComponent::RenderComponent(Mesh* theMesh)
	:mMesh(theMesh)
{
	RenderManager::sGetInstance()->addMeshToPool(mMesh);
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::addMesh(Mesh * theMesh) noexcept
{
	if (mMesh != nullptr)
	{
		RenderManager::sGetInstance()->removeMeshFromPool(mMesh);
	}
	mMesh = theMesh;
	RenderManager::sGetInstance()->addMeshToPool(mMesh);
}
