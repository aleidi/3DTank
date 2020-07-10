#pragma once
#include "Component.h"

class ParticleSystem;

class ShellFlyComponent : public Component {
public:
	ShellFlyComponent(GameObject* obj, const Vector3& direction);
	~ShellFlyComponent();

	void onUpdate(const float& detaTime) override;
	void updateForward(float detaTime);
	void setTarget(GameObject* t);
	void setVelocity(const Vector3& dir);
	void setTankType(const int& type);
	Vector3 getVelocity();

	float count;

private:
	void initParticle();
private:
	float rotateSpeed;
	float angle;
	int tankType;
	int turnCount;
	float normalShellSpeed, trackShellSpeed;
	int maxTurnCount;

	GameObject* target;
	Vector3 finalForward;
	Vector3 velocity;
	Vector3 gracity;

	ParticleSystem* mPS;
};