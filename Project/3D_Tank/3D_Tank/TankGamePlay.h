#pragma once
#include "ScriptComponent.h"

class TankGamePlay : public ScriptComponent
{
public:
	TankGamePlay(GameObject* object) noexcept;
	void onUpdate(const float& deltaTime) override;
};

