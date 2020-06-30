#pragma once
#include "GameObject.h"
#include "CollisionEvent.h"

class MBoundingSphere;
class ShellFlyComponent;
class SoundComponent;

class Shell : GameObject, CollisionEvent {
public:
	Shell(const Vector3& origin, const Vector3& direction, const int& shellType);
	Shell(GameObject* obj, const int& shellType);
	~Shell();

	MBoundingSphere* getCollisionSphere();
	ShellFlyComponent* getShellComponent();
	int getShelltype();
	void onUpdate(float deltaTime) override;

	void onTriggerEnter() override;

	GameObject* shell;
	//GameObject* fireTank;
	GameObject* attactTank;

private:
	MBoundingSphere* mCollisionSphere;
	ShellFlyComponent* mShellFly;
	SoundComponent* mSound;
	Vector3 origin;
	int shellType;
	float mCount;
};