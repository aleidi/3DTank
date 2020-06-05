#pragma once
#include "ScriptComponent.h"

class CameraCtrl : public ScriptComponent
{
public:
	CameraCtrl(GameObject* object) noexcept;
	void onUpdate(float deltaTime) override;

private:
	Transform* mTarget;
};