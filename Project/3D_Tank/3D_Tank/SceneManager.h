#pragma once
#include "EngineCommon.h"
#include "DirectXMath.h"

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
	void createModel(GameObject& obj, const std::string& modelPath, const std::wstring& texturePath);
	void createModel(GameObject& obj, const std::string& modelPath, const std::wstring& texturePath, DirectX::XMVECTOR& maxPoint, DirectX::XMVECTOR& minPoint);

	void addGameObjectToPool(GameObject* object) noexcept;
	bool removeGameObjectFromPool(GameObject* object) noexcept;
	GameObject* findObjectWithName(const std::string& name);
	std::list<std::string> getAllGameobjectName();

	void onGameStart();
	void onUpdate(float deltaTime);
	void onEngineUpdate(float deltaTime);
	void onEngineFixedUpdate(float fixedDeltaTime);
private:
	SceneManager();
	~SceneManager();

	std::list<GameObject*> mObjs;
	std::map<std::string,GameObjectFactory*> mFactories;

	static SceneManager* sInstance;
};

