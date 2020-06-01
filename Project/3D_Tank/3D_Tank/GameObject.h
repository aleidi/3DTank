#pragma once
#include <vector>
#include "EngineCommon.h"

class Component;
class Transform;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void addComponent(Component* comp) noexcept;
	Component* getComponent(int index) const noexcept;
	Transform* getTransform() const noexcept;

private:
	std::vector<Component*> mComps;
};

