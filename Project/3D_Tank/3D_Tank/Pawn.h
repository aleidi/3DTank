#pragma once

#include "GameObject.h"

class MovementComponent;

class Pawn : public GameObject
{
public:
	struct Attribute
	{
		int m_HP;
		float m_AttackRangeRadiusSq;
		float m_PursuitRangeRadiusSq;

		float m_Mass;
		float m_MaxSpeed;
		float m_MaxForce;
		float m_MaxTurnRate;

		Vector3 m_Velocity;
	};

public:
	Pawn();
	virtual ~Pawn();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;


	virtual void move(Vector3 value);

	void setHP(int changeHP);
	int getHP()const;
	void setMass(float mass);
	float getMass()const;
	void setMaxSpeed(float maxspeed);
	float getMaxSpeed()const;
	void setVelocity( Vector3 newVelocity );
	Vector3 getVelocity()const;

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
};