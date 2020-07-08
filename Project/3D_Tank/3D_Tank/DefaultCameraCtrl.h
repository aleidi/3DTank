#pragma once
#include "ScriptComponent.h"

class DefaultCameraCtrl : public ScriptComponent
{
public:
	DefaultCameraCtrl(GameObject* object) noexcept;
	void onUpdate(const float& deltaTime) override;
};

