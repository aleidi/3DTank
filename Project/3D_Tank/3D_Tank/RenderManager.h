#pragma once
#include "Graphics.h"
#include "LightHelper.h"

class Mesh;
class UIBase;
class GameObject;

class RenderManager
{
public:
	static RenderManager* sGetInstance();
	static void createSingleton(Graphics& gfx);
	static void Destroy();

	void onDraw();
	void onPostDraw();

	void addMeshToPool(Mesh* mesh) noexcept;
	bool removeMeshFromPool(Mesh* mesh) noexcept;
	void addUIToPool(UIBase* ui) noexcept;
	bool removeUIFromPool(UIBase* ui) noexcept;

	Graphics& getGraphics() const;
	DirectionalLight getDirLight() noexcept;
	void rotateLight(float x, float y, float z);

private:
	RenderManager(Graphics& gfx);
	~RenderManager();
	RenderManager(const RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;

	void initLight() noexcept;

private:
	static RenderManager* sInstance;

	std::list<Mesh*> mMeshes;
	std::list<UIBase*> mUIs;
	DirectionalLight mDirLight;
	Graphics& mGraphics;
};