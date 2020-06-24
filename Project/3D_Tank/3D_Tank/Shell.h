#pragma once
#include "GameObject.h"

class MBoundingSphere;
class ShellFlyComponent;

class Shell : GameObject {
public:
	Shell(const Vector3& origin, const Vector3& direction, const int& shellType);
	~Shell();

	MBoundingSphere* getCollisionSphere();
	int getShelltype();

	GameObject* shell;

private:
	MBoundingSphere* mCollisionSphere;
	ShellFlyComponent* mShellFly;
	Vector3 origin;
	int shellType;
};