#pragma once
#include "GameObject.h"
#include "CollisionEvent.h"

class MBoundingSphere;
class ShellFlyComponent;

class Shell : GameObject, CollisionEvent {
public:
	Shell(const Vector3& origin, const Vector3& direction, const int& shellType);
	Shell(GameObject* obj, const int& shellType);
	~Shell();

	MBoundingSphere* getCollisionSphere();
	ShellFlyComponent* getShellComponent();
	int getShelltype();

	void onTriggerEnter() override;

	GameObject* shell;
	GameObject* fireTank;

private:
	MBoundingSphere* mCollisionSphere;
	ShellFlyComponent* mShellFly;
	Vector3 origin;
	int shellType;
};