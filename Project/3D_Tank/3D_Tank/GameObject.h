#pragma once
#include "EngineCommon.h"
#include "BoundingCube.h"
#include "BoundingSphere.h"

class Component;
class Transform;
class ScriptComponent;

class GameObject
{
public:
	GameObject();
	~GameObject();

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

	virtual void onStart();
	virtual void onUpdate(float deltaTime);
	void onEngineUpdate(float deltaTime);
	void onEngineFixedUpdate(float fixedDeltaTime);

	void setLastFramePosition(const Vector3& position);
	Vector3 getLastFramePosition();

	BoundingCube* cube;
	MBoundingSphere* sphere;
	DirectX::XMVECTOR Vmax, Vmin;
	bool onCollision;

protected:
	std::list<Component*> mComps;
	Transform* mTransform;

	std::string mName;

private:
	Vector3* lastFramePostion;
};