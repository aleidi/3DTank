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

	void onUpdate(float deltaTime) noexcept;

private:
	std::list<Component*> mComps;
	Transform* mTransform;
};

