#pragma once

// a class defining an enemy tank
#include <string>
#include <cassert>

#include "BaseGameEntity.h"
#include "EnemyTankOwnedStates.h"
// #include "StateMachine.h"
#include "SceneManager.h"
#include "Transform.h"
const int DyingHP = 20; // below this value the enemy tank is dying
const int FullHP = 100;
const int ReplyInterval = 10;

class EnemyTank : public BaseGameEntity {

public:
	struct Attribute
	{
		int HP;
		float AttackRangeRadiusSq;
		float PursuitRangeRadiusSq;
	};

public:
	EnemyTank(int ID);
	~EnemyTank() { } // delete m_pStateMachine; }

	/*
	void update();

	StateMachine<EnemyTank>* getFSM() const { return m_pStateMachine; }
	bool handleMessage(const Telegram& msg);
	*/
	//////////////////////////////////////////////////////accessors
	void setHP(int changeHP);
	int getHP()const;

	bool isDying()const;
	bool isEnemyInRange()const;
	bool isLostEnemy()const;
	bool isAttacked()const { return false; }
	bool isObstacleHere()const { return false; }
	bool getHPRecovered()const;
	void setHPRecovered(bool isRecovered);
	Vector3 getPosPlayer = Vector3(100.0f, 0.0f, 100.0f);


private:
	// StateMachine<EnemyTank>* m_pStateMachine;
	bool m_HPRecovered;
	Attribute mAttribute;
};

