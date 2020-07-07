#pragma once
#include "Component.h"

class ParticleSystem;

class ShellFlyComponent : public Component {
public:
	ShellFlyComponent(GameObject* obj);
	ShellFlyComponent(GameObject* obj, const Vector3& direction);
	~ShellFlyComponent();

	void onUpdate(const float& detaTime) override;
	void updateForward(float detaTime);
	void setTarget(GameObject* t);
	void setVelocity(const Vector3& dir);
	Vector3 getVelocity();

private:
	void initParticle();
private:
	GameObject* target;
	Vector3 finalForward;
	float rotateSpeed;
	float angle;
	//float angle;

	Vector3 velocity;
	Vector3 gracity;

	ParticleSystem* mPS;
};