#pragma once
#include <map>

#include "EngineCommon.h"

class Gameobject;
class Component;
class Transform;
class RenderComponent;

class SceneManager
{
public:
	Gameobject* createCube() const noexcept;
	Gameobject* createSphere() const noexcept;
	Gameobject* createPlane() const noexcept;
	Gameobject* createEmptyObject() const noexcept;
	Transform* createTransform() const noexcept;
	RenderComponent* createRender() const noexcept;
	void destroyGameobject(UINT id) noexcept;
	void destroyComponent(UINT id) noexcept;

private:
	SceneManager();
	~SceneManager();

	static SceneManager instance;

	UINT mObjsID;
	UINT mCompsID;
	std::map<UINT, Gameobject*> mObjs;
	std::map<UINT, Component*> mComps;
};

