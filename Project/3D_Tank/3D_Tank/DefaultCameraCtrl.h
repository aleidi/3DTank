#pragma once
#include "ScriptComponent.h"

class DefaultCameraCtrl : public ScriptComponent
{
public:
	DefaultCameraCtrl(GameObject* object) noexcept;
	void onUpdate(float deltaTime) override;
};

