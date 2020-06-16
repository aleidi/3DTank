#pragma once
#include "EngineCommon.h"
#include "DirectXMath.h"

class GameObject;
class RenderComponent;
class GameObjectFactory;
class UIImage;
class UIButton;

class SceneManager
{
public:
	static SceneManager* sGetInstance();
	static void createSingleton();

	GameObject* createCube() noexcept;
	GameObject* createSphere() noexcept;
	GameObject* createPlane() noexcept;
	GameObject* createEmptyObject() noexcept;
	void createRenderComponent(GameObject* object) noexcept;
	void createModel(GameObject& obj, const std::string& modelPath, const std::wstring& texturePath);
	void createModel(GameObject& obj, const std::string& modelPath, const std::wstring& texturePath, DirectX::XMVECTOR& maxPoint, DirectX::XMVECTOR& minPoint);
	UIImage* createUIImage(const std::wstring& texPath);
	UIButton* createUIButton(const std::wstring& texPath);

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

