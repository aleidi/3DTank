#pragma once
#include "EngineCommon.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void setID(UINT id) noexcept;
	UINT getID() const noexcept;
private:
	UINT mID;
};

