#pragma once
#include "GameObject.h"
#include "CollisionEvent.h"

class MBoundingSphere;
class ShellFlyComponent;
class SoundComponent;

class Shell : public GameObject, CollisionEvent {
public:
	Shell(const Vector3& origin, const Vector3& direction, const int& shellType);
	Shell(const int& shellType);
	Shell(GameObject* obj, const int& shellType);
	~Shell();

	void resetPosAndDir(const Vector3& origin, const Vector3& direction, const int& shellType);
	void resetPosAndDir(const Vector3& origin, const Vector3& direction, const int& shellType, GameObject* obj);

	MBoundingSphere* getCollisionSphere();
	ShellFlyComponent* getShellComponent();
	SoundComponent* getSoundComponent();
	
	int getShelltype();
	void onUpdate(const float& deltaTime) override;
	void onTriggerEnter() override;

	GameObject* shell;
	GameObject* attactTank;

	bool isTrigger;

private:
	MBoundingSphere* mCollisionSphere;
	ShellFlyComponent* mShellFly;
	SoundComponent* mSound;
	Vector3 origin;
	int shellType;
	float mCount;
};