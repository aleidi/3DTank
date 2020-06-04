#pragma once
#include "EngineCommon.h"

class GameObject;

class Component
{
public:
	Component() = delete;
	Component(GameObject* object) noexcept;
	virtual ~Component();
	virtual void onEngineUpdate(float deltaTime) {}

	virtual void onAwake() {}
	virtual void onEnable() {}
	virtual void onStart() {}
	virtual void onUpdate(float deltaTime) {}
	virtual void onFixedUpdate(float deltaTime) {}

	GameObject* getObject() const noexcept;

protected:
	GameObject* mObject;
};