#pragma once
#include "EngineCommon.h"
#include "DirectXMath.h"

class GameObject;
class RenderComponent;
class GameObjectFactory;
class UIImage;
class UIButton;
class UIText;
class UIImage3D;
class AIController;
class UIBase;
class ParticleSystem;
class UIText3D;
class VFXSphere;

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
	RenderComponent* createModel(GameObject& obj, const std::string& modelPath, const std::wstring& texturePath);
	RenderComponent* createModel(GameObject& obj, const std::string& modelPath, const std::wstring& texturePath, DirectX::XMVECTOR& maxPoint, DirectX::XMVECTOR& minPoint);
	UIImage* createUIImage(const std::wstring& texPath);
	UIButton* createUIButton(const std::wstring& texPath);
	UIText* createUIText(const std::wstring& text = L"未设置文本");
	UIImage3D* createUIImage3D(const std::wstring& texPath);
	UIText3D* createUIText3D(const std::wstring& text = L"未设置文本");
	ParticleSystem* createParticleSystem(const std::wstring& texPath, int maxParticles = 1);
	VFXSphere* createVFXSphere();
	void setSkyBox(const std::wstring& texPath);
	
	AIController* createAIController(int id);

	void addGameObjectToPool(GameObject* object) noexcept;
	bool removeAIControllerFromPool(AIController* ctrl) noexcept;
	bool removreUIFromPool(UIBase* ui);
	bool removeUI3DFromPool(UIBase* ui);
	bool removeParticleFromPool(ParticleSystem* particle);
	bool removeVFXSphereFromPool(VFXSphere* s);
	void registerGarbageObj(GameObject* obj);
	GameObject* findObjectWithName(const std::string& name);
	std::list<std::string> getAllGameobjectName();
	AIController* getAIController(int id);

	void onGameStart();
	void onUpdate(float deltaTime);
	void onLateUpdate(float deltaTime);
	void onEngineUpdate(float deltaTime);
	void onEngineFixedUpdate(float fixedDeltaTime);
	void onGarbageCollection();

private:
	bool removeGameObjectFromPool(GameObject* object) noexcept;

private:
	SceneManager();
	~SceneManager();

	std::list<GameObject*> mObjs;
	std::map<int, AIController*> mAIControllers;
	std::map<std::string,GameObjectFactory*> mFactories;

	std::list<GameObject*> mGarbageObjs;

	static SceneManager* sInstance;
};

