#pragma once
#include "EngineCommon.h"

class GameObject;

class Component
{
public:
	Component();
	~Component();

	void setObject(GameObject* obj) noexcept;
	GameObject* getObject() const noexcept;
	void setID(UINT id) noexcept;
	UINT getID() const noexcept;

private:
	GameObject* mObject;
	UINT mID;
};