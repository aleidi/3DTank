#include "RenderManager.h"
#include "Mesh.h"
#include "LightHelper.h"
#include "GameObject.h"
#include "Transform.h"
#include "UIBase.h"
#include "ParticleSystem.h"
#include "VFXSphere.h"
#include "Blender.h"
#include "DepthStencil.h"

#include <algorithm>
#include <memory>
#include <vector>

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
	static std::unique_ptr<Blender> sOpaqueBlend;
	static std::unique_ptr<Blender> sAlphaBlend;
	static std::unique_ptr<DepthStencil> sDepthWrite;
	static std::unique_ptr<DepthStencil> sDepthReadOnly;

	if (sOpaqueBlend == nullptr)
	{
		sOpaqueBlend = std::make_unique<Blender>(mGraphics, Blender::BlendMode::Opaque);
		sAlphaBlend = std::make_unique<Blender>(mGraphics, Blender::BlendMode::AlphaBlend, false);
		sDepthWrite = std::make_unique<DepthStencil>(mGraphics, DepthStencil::DepthMode::DepthWrite);
		sDepthReadOnly = std::make_unique<DepthStencil>(mGraphics, DepthStencil::DepthMode::DepthReadOnly);
	}

	std::vector<Mesh*> transparentMeshes;

	// 1) Opaque pass
	sOpaqueBlend->bind(mGraphics);
	sDepthWrite->bind(mGraphics);

	for (std::list<Mesh*>::iterator it = mMeshes.begin(); it != mMeshes.end(); ++it)
	{
		if (nullptr == *it)
		{
			continue;
		}

		if (!(*it)->isTransparent())
		{
			(*it)->draw(mGraphics);
		}
		else
		{
			transparentMeshes.push_back(*it);
		}
	}

	// 2) Skybox before transparent pass
	mGraphics.DrawSkyBox();

	// 3) Transparent pass
	XMFLOAT3 camPos;
	XMStoreFloat3(&camPos, mGraphics.getCameraPosition());

	auto distSq = [&](Mesh* mesh)
	{
		XMFLOAT4X4 m;
		XMStoreFloat4x4(&m, mesh->getTransformXM());
		const float dx = m._41 - camPos.x;
		const float dy = m._42 - camPos.y;
		const float dz = m._43 - camPos.z;
		return dx * dx + dy * dy + dz * dz;
	};

	std::sort(transparentMeshes.begin(), transparentMeshes.end(),
		[&](Mesh* a, Mesh* b)
		{
			return distSq(a) > distSq(b);
		});

	sAlphaBlend->bind(mGraphics);
	sDepthReadOnly->bind(mGraphics);

	for (std::vector<Mesh*>::iterator it = transparentMeshes.begin(); it != transparentMeshes.end(); ++it)
	{
		(*it)->draw(mGraphics);
	}

	// Restore default state for post draw
	sOpaqueBlend->bind(mGraphics);
	sDepthWrite->bind(mGraphics);

	for (std::list<VFXSphere*>::iterator it = mVFXs.begin(); it != mVFXs.end(); ++it)
	{
		if (nullptr == *it)
		{
			continue;
		}
		(*it)->draw(mGraphics);
	}
}

void RenderManager::onPostDraw(const float& deltaTime)
{
	static std::unique_ptr<Blender> sAlphaBlend;
	static std::unique_ptr<DepthStencil> sDepthWrite;
	static std::unique_ptr<DepthStencil> sDepthReadOnly;

	if (sAlphaBlend == nullptr)
	{
		sAlphaBlend = std::make_unique<Blender>(mGraphics, Blender::BlendMode::AlphaBlend, false);
		sDepthWrite = std::make_unique<DepthStencil>(mGraphics, DepthStencil::DepthMode::DepthWrite);
		sDepthReadOnly = std::make_unique<DepthStencil>(mGraphics, DepthStencil::DepthMode::DepthReadOnly);
	}

	// 3D UI / particles: keep depth test, disable depth writes to avoid self-fighting
	sAlphaBlend->bind(mGraphics);
	sDepthReadOnly->bind(mGraphics);

	for (std::list<UIBase*>::iterator it = mUISPs.begin(); it != mUISPs.end(); ++it)
	{
		if (nullptr == *it)
		{
			continue;
		}
		(*it)->draw(mGraphics);
	}

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

	// Restore normal state for screen-space UI
	sDepthWrite->bind(mGraphics);

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

bool RenderManager::removeUI3DFromPool(UIBase * ui, bool isSp) noexcept
{
	if (isSp != true)
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
	}
	else
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

void RenderManager::rotateLight(const float& x, const float& y, const float& z)
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
