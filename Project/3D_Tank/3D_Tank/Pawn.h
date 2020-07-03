#pragma once

#include "GameObject.h"
#include "CollisionEvent.h"

class MovementComponent;
class UIHP;

enum MoveDirection{
	FORWARD, MBACK, RIGHT, LEFT
};

enum LeftRightDirection {
	MLEFT, MRIGHT
};

class Pawn : public GameObject, public CollisionEvent
{
public:
	struct Attribute
	{
		int m_HP;
		int FullHP;
		float m_AttackRangeRadiusSq;
		float m_PursuitRangeRadiusSq;
		float m_WanderRangeRadiusSq;

		float m_Mass;
		float m_MaxSpeed;

		float m_AttackTimeDelay;
		float m_Offset;
		int m_HitRate;
		//float m_MaxForce;
		float m_MaxTurnRate;

		float m_WanderRadius;
		float m_WanderDistance;
		float m_WanderJitter;

		Vector3 m_ResetPoint;
		Vector3 m_WanderTarget;
	};

public:
	Pawn();
	virtual ~Pawn();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;

	virtual void move(Vector3 value);
	virtual void attack(Vector3 battery_position, Vector3 shot_direction);
	virtual void attack(Vector3 battery_position, Vector3 shot_direction,Pawn* target);
	virtual void hited(int value);

	virtual void onTriggerEnter(const GameObject* obj) override;
	virtual void onCollisionEnter() override;

	enum MoveDirection moveDirection;
	enum LeftRightDirection rotateDirection;
	void setHP(int changeHP);
	int getHP()const;
	void setMass(float mass);
	float getMass()const;
	void setMaxSpeed(float maxspeed);
	float getMaxSpeed()const;
	void setVelocity( Vector3 newVelocity );
	Vector3 getVelocity()const;

	bool isAlive()const { if (mAttribute.m_HP > 0) return true; else return false; }
	bool isDying()const;
	bool isEnemyInRange()const;
	bool isLostEnemy()const;
	bool isAttacked()const;
	bool isObstacleHere()const;
	bool getHPRecovered()const;
	void setHPRecovered(bool isRecovered);
protected:
	MovementComponent* mMovementComp;
	Attribute mAttribute;
	Vector3 m_Velocity;

	UIHP* mUIHP;
};