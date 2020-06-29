#pragma once
#include "EngineCommon.h"
#include "BoundingCube.h"
#include "BoundingSphere.h"

class Component;
class Transform;
class ScriptComponent;
class SoundComponent;

class GameObject
{
public:
	enum CollisionLayer
	{
		StaticObject = 0,
		DynamicObject = 1,
		AttackAble = 2,
	};

public:

	GameObject();
	virtual ~GameObject();
	GameObject(GameObject& obj);

	void addComponent(Component* comp) noexcept;
	void addScriptComponent(ScriptComponent* comp) noexcept;
	bool removeComponent(Component* comp);

	template<typename T = Component>
	T* getComponent();

	template<typename T>
	std::vector<T*> getComponents();

	Transform* getTransform() const noexcept;
	std::string getName() const noexcept;
	void setName(const std::string& name) noexcept;

	GameObject* find(const std::string& name);
	void attach(const GameObject& obj) noexcept;
	void attach(Transform& transform) noexcept;
	bool hasParent() noexcept;
	void deAttach() noexcept;
	void destroy();

	virtual void onStart();
	virtual void onUpdate(float deltaTime);
	virtual void onLateUpdate(float deltaTime);
	void onEngineUpdate(float deltaTime);
	void onEngineFixedUpdate(float fixedDeltaTime);

	void setLastFramePosition(const Vector3& position);
	Vector3 getLastFramePosition();
	CollisionLayer getCollisionLayer();

	BoundingCube* cube;
	MBoundingSphere* sphere;
	SoundComponent* sound;
	DirectX::XMVECTOR Vmax, Vmin;
	bool onCollision;

protected:
	std::list<Component*> mComps;
	Transform* mTransform;

	std::string mName;
	CollisionLayer mColLayer;
private:
	Vector3* lastFramePostion;
};