#pragma once
#include "MovementComponent.h"
#include "EnemyTank.h"
class AIMovementComponent : public MovementComponent
{
public:
	AIMovementComponent(EnemyTank* enemy);
	~AIMovementComponent();

	void onUpdate(float deltaTime);
	void addVelocity(Vector3 value);
	void addForce(Vector3 value);

protected:
	bool isStart = false;
	Vector3 force;
	float mass;
	float maxSpeed;
	Vector3 position = Vector3::zero;
	Vector3 acceleration = Vector3::zero, velocity = Vector3::zero;

	Pawn* m_enemy;
};