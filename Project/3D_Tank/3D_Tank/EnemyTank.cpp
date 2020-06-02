#include "EnemyTank.h"
/*
EnemyTank::EnemyTank(int id) : m_HP(0),
                               BaseGameEntity(id)
{
	m_pStateMachine = new StateMachine<EnemyTank>(this);
	// m_pStateMachine->setCurrentState( A_STATE::Instance() );
	// m_pStateMachine->setGlobalState( EnemyTankGlobalState::Instance() );
}*/

EnemyTank::~EnemyTank() { delete m_pStateMachine; }
							  
void EnemyTank::update() {
	m_pStateMachine->update();
}

StateMachine<EnemyTank>* EnemyTank::getFSM()const {
	return m_pStateMachine;
}
