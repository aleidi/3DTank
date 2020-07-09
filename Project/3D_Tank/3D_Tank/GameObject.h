#pragma once
#include "EngineCommon.h"
#include "BoundingCube.h"
#include "BoundingSphere.h"

class Component;
class Transform;
class ScriptComponent;
class SoundComponent;
class RenderComponent;

class GameObject
{
public:
	enum CollisionLayer
	{
		StaticObject = 0,
		DynamicObject = 1,
		AttackAble = 2,
	};

	enum ObjectTag
	{
		Environment = 0,
		Player = 1,
		Enemy =2,
	};

public:

	GameObject();
	GameObject(int value);
	virtual ~GameObject();
	GameObject(GameObject& obj);

	void addComponent(Component* comp) noexcept;
	void addScriptComponent(ScriptComponent* comp) noexcept;
	bool removeComponent(Component* comp);

	template<typename T = Component>
	T* getComponent()
	{
		for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
		{
			T* c = dynamic_cast<T*>(*it);
			if (c != nullptr)
			{
				return c;
			}
		}
		return nullptr;
	}

	template<typename T>
	std::vector<T*> getComponents()
	{
		std::vector<T*>list;
		for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
		{
			T* c = dynamic_cast<T*>(*it);
			if (c != nullptr)
			{
				list.push_back(*it);

			}
		}
		return list;
	}

	Transform* getTransform() const noexcept;
	std::string getName() const noexcept;
	void setName(const std::string& name) noexcept;
	void enableDraw(bool value);

	GameObject* find(const std::string& name);
	void attach(const GameObject& obj) noexcept;
	void attach(Transform& transform) noexcept;
	bool hasParent() noexcept;
	void deAttach() noexcept;
	virtual void destroy();

	virtual void onStart();
	virtual void onUpdate(const float& deltaTime);
	virtual void onLateUpdate(const float& deltaTime);
	void onEngineUpdate(const float& deltaTime);
	void onEngineFixedUpdate(const float& fixedDeltaTime);

	void setLastFramePosition(const Vector3& position);
	Vector3 getLastFramePosition();
	CollisionLayer getCollisionLayer() const;
	ObjectTag getTag() const;

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
	ObjectTag mTag;
private:
	Vector3* lastFramePostion;
};