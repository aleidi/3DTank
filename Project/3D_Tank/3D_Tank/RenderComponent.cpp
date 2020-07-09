#include "RenderComponent.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"

RenderComponent::RenderComponent(GameObject* obj)
	:Component(obj),mMesh()
{
	initMaterial();
}

RenderComponent::~RenderComponent()
{
	if (mMesh != nullptr)
	{
		RenderManager::sGetInstance()->removeMeshFromPool(mMesh);
	}
	mMesh = nullptr;
}

void RenderComponent::setMesh(Mesh * theMesh) noexcept
{
	if (mMesh != nullptr)
	{
		RenderManager::sGetInstance()->removeMeshFromPool(mMesh);
	}
	mMesh = theMesh;
	RenderManager::sGetInstance()->addMeshToPool(mMesh);
	mMesh->setMaterial(mMaterial);
}

DirectX::XMMATRIX RenderComponent::getWorldMatrix() noexcept
{
	return mObject->getTransform()->getLocalToWorldMatrix();
}

Material RenderComponent::getMaterial() const noexcept
{
	return mMaterial;
}

void RenderComponent::setMaterial(Material mat) noexcept
{
	mMaterial = mat;
	mMesh->setMaterial(mat);
}

void RenderComponent::enableDraw(bool value) noexcept
{
	mMesh->enableDraw(value);
}

void RenderComponent::initMaterial()
{
	mMaterial.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mMaterial.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mMaterial.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);
	mMaterial.Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
}
