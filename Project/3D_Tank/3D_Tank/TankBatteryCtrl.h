#pragma once
#include "ScriptComponent.h"

class TankBatteryCtrl : public ScriptComponent
{
public:
	TankBatteryCtrl(GameObject* object) noexcept;
	void onUpdate(float deltaTime) override;
};

