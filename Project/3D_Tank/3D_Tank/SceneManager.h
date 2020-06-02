#pragma once
#include "EngineCommon.h"

class GameObject;
class RenderComponent;
class GameObjectFactory;

class SceneManager
{
public:
	static SceneManager* sGetInstance();
	static void createSingleton();

	GameObject* createCube() const noexcept;
	GameObject* createSphere() const noexcept;
	GameObject* createPlane() const noexcept;
	GameObject* createEmptyObject() const noexcept;
	void createRenderComponent(GameObject* object) const noexcept;

	void addGameObjectToPool(GameObject* object) noexcept;
	bool removeGameObjectToPool(GameObject* object) noexcept;

	void onUpdate(float deltaTime);
private:
	SceneManager();
	~SceneManager();

	std::list<GameObject*> mObjs;
	std::map<std::string,GameObjectFactory*> mFactories;

	static SceneManager* sInstance;
};

