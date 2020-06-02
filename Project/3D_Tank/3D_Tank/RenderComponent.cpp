#include "RenderComponent.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "Transform.h"

RenderComponent::RenderComponent(GameObject* obj, Mesh* theMesh)
	:Component(obj),mMesh(theMesh)
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

DirectX::XMMATRIX RenderComponent::getTransformXM() noexcept
{
	return mObject->getTransform()->getLoacalToWorldMatrix();
}
