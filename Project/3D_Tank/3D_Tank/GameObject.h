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

	void setID(UINT id) noexcept;
	UINT getID() const noexcept;
	void addComponent(Component* comp) noexcept;
	Component* getComponent(int index) const noexcept;
	Transform* getTransform() const noexcept;

private:
	UINT mID;
	std::vector<Component*> mComps;
};

