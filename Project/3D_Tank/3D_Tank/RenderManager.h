#pragma once
#include "Graphics.h"

class Mesh;

class RenderManager
{
public:
	static RenderManager* sGetInstance();
	static void createSingleton(Graphics& gfx);
	static void Destroy();

	void onDraw() noexcept;

	void addMeshToPool(Mesh* mesh) noexcept;
	bool removeMeshFromPool(Mesh* mesh) noexcept;
	Graphics& getGraphics() const;

private:
	RenderManager(Graphics& gfx);
	~RenderManager();
	RenderManager(const RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;
private:
	static RenderManager* sInstance;

	std::list<Mesh*> mMeshes;
	Graphics& mGraphics;
};