#pragma once
#include "EngineCommon.h"

class GameObject;

class Component
{
public:
	Component() = default;
	Component(GameObject* object);
	~Component();

	virtual void onAwake() {}
	virtual void onEnable() {}
	virtual void onStart() {}
	virtual void onUpdate(float deltaTime) {}

	void setObject(GameObject* obj) noexcept;
	GameObject* getObject() const noexcept;

private:
	GameObject* mObject;
};