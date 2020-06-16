#include "RenderManager.h"
#include "Mesh.h"
#include "LightHelper.h"
#include "GameObject.h"
#include "Transform.h"
#include "UIBase.h"

RenderManager* RenderManager::sInstance = nullptr;

RenderManager * RenderManager::sGetInstance()
{
	return sInstance;
}

void RenderManager::createSingleton(Graphics & gfx)
{
	assert(!sInstance);
	sInstance = new RenderManager(gfx);
}

void RenderManager::Destroy()
{
	delete sInstance;
	sInstance = nullptr;
}

void RenderManager::onDraw() noexcept
{
	for (std::list<Mesh*>::iterator it = mMeshes.begin(); it != mMeshes.end(); ++it)
	{
		if (nullptr == *it)
		{
			continue;
		}
		(*it)->draw(mGraphics);
	}
}

void RenderManager::addMeshToPool(Mesh * mesh) noexcept
{
	mMeshes.push_back(mesh);
}

bool RenderManager::removeMeshFromPool(Mesh * mesh) noexcept
{
	for (std::list<Mesh*>::iterator it = mMeshes.begin(); it != mMeshes.end();)
	{
		if (*it == mesh)
		{
			delete *it;
			*it = nullptr;
			mMeshes.erase(it++);
			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

void RenderManager::addUIToPool(UIBase * ui) noexcept
{
	mUIs.push_back(ui);
}

bool RenderManager::removeUIFromPool(UIBase * ui) noexcept
{
	for (std::list<UIBase*>::iterator it = mUIs.begin(); it != mUIs.end();)
	{
		if (*it == ui)
		{
			delete *it;
			*it = nullptr;
			mUIs.erase(it++);
			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

Graphics & RenderManager::getGraphics() const
{
	return mGraphics;
}

DirectionalLight RenderManager::getDirLight() noexcept
{
	return mDirLight;
}

void RenderManager::rotateLight(float x, float y, float z)
{
	XMVECTOR dir = XMLoadFloat3(&mDirLight.Direction);
	dir = XMVector3Rotate(dir, XMQuaternionRotationRollPitchYaw(
		XMConvertToRadians(x),
		XMConvertToRadians(y),
		XMConvertToRadians(z)));
	dir = XMVector3Normalize(dir);
	XMStoreFloat3(&mDirLight.Direction, dir);
}

RenderManager::RenderManager(Graphics & gfx)
	:mMeshes(), mGraphics(gfx)
{
	initLight();
}

RenderManager::~RenderManager()
{
	for (std::list<Mesh*>::iterator it = mMeshes.begin(); it != mMeshes.end(); ++it)
	{
		if (nullptr != *it)
		{
			delete *it;
			*it = nullptr;
		}
	}
	mMeshes.clear();
}

void RenderManager::initLight() noexcept
{
	mDirLight.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mDirLight.Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	mDirLight.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mDirLight.Direction = XMFLOAT3(-0.577f, -0.577f, 0.577f);
}
