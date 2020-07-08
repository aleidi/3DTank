#pragma once

#include "GameObject.h"
#include "CollisionEvent.h"

class MovementComponent;
class UIHP;
class SoundComponent;

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
		int FullHP; // not initial by FileManger
		int m_AttackMode;
		int m_MoveMode;
		int m_HitRate;
		float m_AttackRangeRadiusSq;
		float m_PursuitRangeRadiusSq;
		float m_WanderRangeRadiusSq;

		float m_Mass;
		float m_Offset;
		float m_MaxSpeed;
		float m_MaxTurnRate;
		float m_AttackTimeDelay;

		float m_WanderRadius;
		float m_WanderDistance;
		float m_WanderJitter;
		Vector3 m_PatrolStart;
		Vector3 m_PatrolEnd;
		Vector3 m_ResetPoint;
		Vector3 m_WanderTarget; //not initial by FileManger
	};

public:
	Pawn();
	virtual ~Pawn();

	virtual void onStart() override;
	virtual void onUpdate(const float& deltaTime) override;
	virtual void onLateUpdate(const float& deltaTime) override;

	virtual void move(Vector3 value);
	virtual void attack(Vector3 battery_position, Vector3 shot_direction);
	virtual void attack(Vector3 battery_position, Vector3 shot_direction,Pawn* target);
	virtual void hited(int value);

	virtual void onTriggerEnter(const GameObject* obj) override;
	virtual void onCollisionEnter() override;

	enum MoveDirection moveDirection;
	enum LeftRightDirection rotateDirection;
	void addHP(int value);
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
	SoundComponent* tankSound;

	UIHP* mUIHP;
};