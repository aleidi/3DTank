#include "RenderManager.h"
#include "Mesh.h"
#include "LightHelper.h"
#include "GameObject.h"
#include "Transform.h"
#include "UIBase.h"
#include "ParticleSystem.h"
#include "VFXSphere.h"

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

void RenderManager::onDraw()
{
	for (std::list<UIBase*>::iterator it = mUISPs.begin(); it != mUISPs.end(); ++it)
	{
		if (nullptr == *it)
		{
			continue;
		}
		(*it)->draw(mGraphics);
	}

	for (std::list<Mesh*>::iterator it = mMeshes.begin(); it != mMeshes.end(); ++it)
	{
		if (nullptr == *it)
		{
			continue;
		}
		(*it)->draw(mGraphics);
	}

	for (std::list<VFXSphere*>::iterator it = mVFXs.begin(); it != mVFXs.end(); ++it)
	{
		if (nullptr == *it)
		{
			continue;
		}
		(*it)->draw(mGraphics);
	}
}

void RenderManager::onPostDraw(float deltaTime)
{
	for (std::list<ParticleSystem*>::iterator it = mParticles.begin(); it != mParticles.end(); ++it)
	{
		if (nullptr == *it)
		{
			continue;
		}
		(*it)->draw(mGraphics, deltaTime);
	}

	for (std::list<UIBase*>::iterator it = mUI3Ds.begin(); it != mUI3Ds.end(); ++it)
	{
		if (nullptr == *it)
		{
			continue;
		}
		(*it)->draw(mGraphics);
	}

	for (std::list<UIBase*>::iterator it = mUIs.begin(); it != mUIs.end(); ++it)
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

void RenderManager::addUI3DToPool(UIBase * ui, bool isSp) noexcept
{
	if (isSp != true)
	{
		mUI3Ds.push_back(ui);
		return;
	}
	mUISPs.push_back(ui);
}

bool RenderManager::removeUI3DFromPool(UIBase * ui) noexcept
{
	for (std::list<UIBase*>::iterator it = mUI3Ds.begin(); it != mUI3Ds.end();)
	{
		if (*it == ui)
		{
			delete *it;
			*it = nullptr;
			mUI3Ds.erase(it++);
			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

void RenderManager::addParticleToPool(ParticleSystem * p) noexcept
{
	mParticles.push_back(p);
}

bool RenderManager::removeParticleFromPool(ParticleSystem * p) noexcept
{
	for (std::list<ParticleSystem*>::iterator it = mParticles.begin(); it != mParticles.end();)
	{
		if (*it == p)
		{
			delete *it;
			*it = nullptr;
			mParticles.erase(it++);
			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

void RenderManager::addVFXToPool(VFXSphere * vfx) noexcept
{
	mVFXs.push_back(vfx);
}

bool RenderManager::removeVFXFromPool(VFXSphere * vfx) noexcept
{
	for (std::list<VFXSphere*>::iterator it = mVFXs.begin(); it != mVFXs.end();)
	{
		if (*it == vfx)
		{
			delete *it;
			*it = nullptr;
			mVFXs.erase(it++);
			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

bool RenderManager::removeUISPFromSpecial(UIBase * ui) noexcept
{
	for (std::list<UIBase*>::iterator it = mUISPs.begin(); it != mUISPs.end();)
	{
		if (*it == ui)
		{
			delete *it;
			*it = nullptr;
			mUISPs.erase(it++);
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

void RenderManager::setSkyBox(const std::wstring & texture)
{
	mGraphics.SetSkyBox(texture);
}

RenderManager::RenderManager(Graphics & gfx)
	:mMeshes(), mUI3Ds(), mUIs(), mParticles(), mGraphics(gfx)
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
