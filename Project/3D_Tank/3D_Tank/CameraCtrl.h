#pragma once
#include "ScriptComponent.h"

class CameraCtrl : public ScriptComponent
{
public:
	CameraCtrl(GameObject* object) noexcept;
	void onUpdate(const float& deltaTime) override;

private:
	Transform* mTarget;
};