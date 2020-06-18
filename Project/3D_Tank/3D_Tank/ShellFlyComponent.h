#pragma once
#include "Component.h"

class ShellFlyComponent : public Component {
public:
	ShellFlyComponent(GameObject* obj);
	~ShellFlyComponent();

	void onUpdate(float detaTime) override;

private:
	Vector3 velocity;
	Vector3 gracity;
};