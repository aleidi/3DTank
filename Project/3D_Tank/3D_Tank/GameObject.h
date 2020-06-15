#pragma once
#include "EngineCommon.h"
#include "BoundingCube.h"

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
	template<typename T>
	T* getComponent(T* t) const noexcept;
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
	DirectX::XMVECTOR Vmax, Vmin;

protected:
	std::list<Component*> mComps;
	Transform* mTransform;

	std::string mName;

private:
	Vector3* lastFramePostion;
};