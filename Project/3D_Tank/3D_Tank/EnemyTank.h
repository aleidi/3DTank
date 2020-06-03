#pragma once
#include <assert.h>
#include "BaseGameEntity.h"
#include "StateMachine.h"

class EnemyTank : public BaseGameEntity {
public:
	EnemyTank(int ID);
	~EnemyTank();

	void update();
	StateMachine<EnemyTank>* getFSM() const;
private:
	StateMachine<EnemyTank>* m_pStateMachine;
	int m_HP;
};

