#include "AIMovementComponent.h"
#include "Math.h"

AIMovementComponent::AIMovementComponent(EnemyTank* enemy) : MovementComponent(enemy)
{
	mass = enemy->getMass();
	maxSpeed = enemy->getMaxSpeed();
	velocity = Vector3::zero;
	position = Vector3::zero;

	m_enemy = enemy;
}

AIMovementComponent::~AIMovementComponent()
{
}

void AIMovementComponent::onUpdate(const float& deltaTime)
{
	if (isStart)
	{
		Vector3 acceleraion = force / mass;
		if(Vector3::lengthSq(velocity, Vector3(0, 0, 0)) < 0.001 )
			velocity = mTransform->Forward * 0.1f;

		velocity += acceleraion * deltaTime;
	
		if (Vector3::lengthSq(velocity, Vector3(0, 0, 0)) > (maxSpeed*maxSpeed))
			velocity = velocity.normalize() * maxSpeed;

		m_enemy->setVelocity(velocity);

		Vector3 newPos = velocity * deltaTime;
		Vector3 newPos_normalize = force.normalize();
		addVelocity(newPos);
	

		Vector3 forward = mTransform->Forward;
		Vector3 forward_normalize = forward.normalize();
		float dot = Vector3::dot(velocity.normalize(), forward_normalize);
		dot = Math::Clamp(1.0f, -1.0f, dot);
		float rotate = acosf(dot) * 180 / Pi;

		Vector3 cross = Vector3::cross(velocity.normalize(), forward_normalize);
		if (cross.y > 0)
		{
			rotate = -rotate;
		}

		if (rotate >= 1.0f || rotate <= -1.0f)
		{	mTransform->rotate(0, rotate, 0);
		}
		
		isStart = false;
	}

	else if (velocity != Vector3(0, 0, 0)) {
		velocity += velocity * -1.0f * deltaTime;
		Vector3 newPos = velocity * deltaTime;
		addVelocity(newPos);
	}

}

void AIMovementComponent::addVelocity(Vector3 value)
{
	mTransform->translate(value);
}

void AIMovementComponent::addForce(Vector3 value)
{
	force = value;
	if( force != Vector3::zero )
		isStart = true;
	else isStart = false;
}
