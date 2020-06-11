#pragma once

// a class defining an enemy tank
#include <string>
#include <cassert>

#include "BaseGameEntity.h"
#include "EnemyTankOwnedStates.h"
#include "StateMachine.h"

const int DyingHP = 20; // below this value the enemy tank is dying
const int FullHP = 0;

class EnemyTank : public BaseGameEntity {
public:
	EnemyTank(int ID);
	~EnemyTank();

	void update();

	StateMachine<EnemyTank>* getFSM() const;
	bool handleMessage(const Telegram& msg);

	void damageCalculaion(int damage);
	int getHP()const;

	bool isDying()const;
	bool isEnemyFound()const;
	Vector3 getPosPlayer;

private:
	StateMachine<EnemyTank>* m_pStateMachine;
	int m_HP;
	float m_AttackRangeRadiusSq;
	Vector3 m_Position;
};

