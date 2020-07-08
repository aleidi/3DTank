#pragma once
#include "EngineCommon.h"

class GameObject;

class Component
{
public:
	Component() = delete;
	Component(GameObject* object) noexcept;
	virtual ~Component();
	virtual void onEngineUpdate(const float& deltaTime) {}
	virtual void onEngineFixedUpdate(const float& fixeDeltaTime) {}

	virtual void onAwake() {}
	virtual void onEnable() {}
	virtual void onStart() {}
	virtual void onUpdate(const float& deltaTime) {}
	virtual void onLateUpdate(const float& deltaTime) {}
	virtual void onFixedUpdate(const float& deltaTime) {}

	GameObject* getObject() noexcept;

protected:
	GameObject* mObject;
};