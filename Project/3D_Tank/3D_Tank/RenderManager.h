#pragma once
#include "Graphics.h"

class Mesh;

class RenderManager
{
public:
	static RenderManager* sGetInstance();
	static void createSingleton(Graphics& gfx);
	static void Destroy();

	void addMeshToPool(Mesh* mesh);
	void removeMeshFromPool(Mesh* mesh);
	Graphics& getGraphics() const;
private:
	RenderManager(Graphics& gfx);
	RenderManager(const RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;

private:
	static RenderManager* sInstance;

	std::list<Mesh*> mMeshes;
	Graphics& mGraphics;
};