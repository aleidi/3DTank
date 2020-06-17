#pragma once

#include "GameObject.h"

class MovementComponent;

class Pawn : public GameObject
{
public:
	struct Attribute
	{
		int HP;
		float AttackRangeRadiusSq;
		float PursuitRangeRadiusSq;
	};

public:
	Pawn();
	virtual ~Pawn();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;


	int getID()const;

	void setHP(int changeHP);
	int getHP()const;
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