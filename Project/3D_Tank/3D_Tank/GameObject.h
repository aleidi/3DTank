#pragma once
#include "EngineCommon.h"

class Component;
class Transform;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void addComponent(Component* comp) noexcept;
	bool removeComponent(Component* comp);
	template<typename T>
	T* getComponent(T* t) const noexcept;
	Transform* getTransform() const noexcept;
	const std::string& getName() const noexcept;
	void setName(const std::string& name) noexcept;

	GameObject* find(const std::string& name);
	void attach(const GameObject& obj) noexcept;
	void attach(Transform& transform) noexcept;
	bool hasParent() noexcept;
	void deAttach() noexcept;

	void onUpdate(float deltaTime);

private:
	std::list<Component*> mComps;
	Transform* mTransform;

	std::string mName;
};