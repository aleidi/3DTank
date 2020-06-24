#pragma once
#include "Component.h"

class ShellFlyComponent : public Component {
public:
	ShellFlyComponent(GameObject* obj);
	ShellFlyComponent(GameObject* obj, const Vector3& direction);
	~ShellFlyComponent();

	void onUpdate(float detaTime) override;
	void updateForward(float detaTime);
	void setTarget(GameObject* t);

private:
	GameObject* target;
	Vector3 finalForward;
	float rotateSpeed;
	float angle;
	//float angle;

	Vector3 velocity;
	Vector3 gracity;
};