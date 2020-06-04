#pragma once

// a class defining an enemy tank
#include <string>
#include <cassert>

#include "BaseGameEntity.h"
#include "EnemyTankOwnedStates.h"
#include "StateMachine.h"

const int DyingHP = 20; // below this value the enemy tank is dying

class EnemyTank : public BaseGameEntity {
public:
	EnemyTank(int ID);
	~EnemyTank();

	void update();

	StateMachine<EnemyTank>* getFSM() const;

	void damageCalculaion(int damage);
	int getHP()const;
	bool isDying()const;
private:
	StateMachine<EnemyTank>* m_pStateMachine;
	int m_HP;
};

