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

private:
	SceneManager();
	~SceneManager();

	static SceneManager instance;
};

