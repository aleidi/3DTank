#include "RenderComponent.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "Transform.h"

RenderComponent::RenderComponent(GameObject* obj)
	:Component(obj),mMesh()
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::setMesh(Mesh * theMesh) noexcept
{
	if (mMesh != nullptr)
	{
		RenderManager::sGetInstance()->removeMeshFromPool(mMesh);
	}
	mMesh = theMesh;
	RenderManager::sGetInstance()->addMeshToPool(mMesh);
}

DirectX::XMMATRIX RenderComponent::getWorldMatrix() noexcept
{
	return mObject->getTransform()->getLocalToWorldMatrix();
}
