#pragma once
#include "EngineCommon.h"

class GameObject;

class Component
{
public:
	Component() = delete;
	Component(GameObject* object);
	virtual ~Component();

	virtual void onAwake() {}
	virtual void onEnable() {}
	virtual void onStart() {}
	virtual void onUpdate(float deltaTime) {}
	virtual void onFixedUpdate(float deltaTime) {}

	void setObject(GameObject* obj) noexcept;
	GameObject* getObject() const noexcept;

protected:
	GameObject* mObject;
};