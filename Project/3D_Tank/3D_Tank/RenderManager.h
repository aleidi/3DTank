#pragma once
#include "Graphics.h"
#include "LightHelper.h"

class Mesh;
class UIBase;
class GameObject;
class ParticleSystem;
class VFXSphere;

class RenderManager
{
public:
	static RenderManager* sGetInstance();
	static void createSingleton(Graphics& gfx);
	static void Destroy();

	void onDraw();
	void onPostDraw(float deltaTime);

	void addMeshToPool(Mesh* mesh) noexcept;
	bool removeMeshFromPool(Mesh* mesh) noexcept;
	void addUIToPool(UIBase* ui) noexcept;
	bool removeUIFromPool(UIBase* ui) noexcept;
	void addUI3DToPool(UIBase* ui) noexcept;
	bool removeUI3DFromPool(UIBase* ui) noexcept;
	void addParticleToPool(ParticleSystem* p) noexcept;
	bool removeParticleFromPool(ParticleSystem* p) noexcept;
	void addVFXToPool(VFXSphere* vfx) noexcept;
	bool removeVFXFromPool(VFXSphere* vfx) noexcept;

	Graphics& getGraphics() const;
	DirectionalLight getDirLight() noexcept;
	void rotateLight(float x, float y, float z);
	void setSkyBox(const std::wstring& texture);

private:
	RenderManager(Graphics& gfx);
	~RenderManager();
	RenderManager(const RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;

	void initLight() noexcept;

private:
	static RenderManager* sInstance;

	std::list<Mesh*> mMeshes;
	std::list<UIBase*> mUI3Ds;
	std::list<UIBase*> mUIs;
	std::list<ParticleSystem*> mParticles;
	std::list<VFXSphere*> mVFXs;
	DirectionalLight mDirLight;
	Graphics& mGraphics;
};