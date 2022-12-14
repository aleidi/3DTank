#pragma once
#include "GameObject.h"
#include "CollisionEvent.h"

class MBoundingSphere;
class ShellFlyComponent;
class SoundComponent;
class VFXSphere;

class Shell : public GameObject, CollisionEvent {
public:
	Shell();
	Shell(const Vector3& origin, const Vector3& direction, const int& shellType);
	Shell(const Vector3& origin, const Vector3& direction, const int& shellType, const int& enemyType);
	~Shell();

	void resetPosAndDir(const Vector3& origin, const Vector3& direction, const int& shellType, const int& enemyType);
	void resetPosAndDir(const Vector3& origin, const Vector3& direction, const int& shellType, GameObject* obj, const int& enemyType);

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
	int tankType;
	float mCount;
	VFXSphere* mModel;
};