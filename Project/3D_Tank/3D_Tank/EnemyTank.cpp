#include "EnemyTank.h"

EnemyTank::EnemyTank(int id) : BaseGameEntity(id),
							   m_HP(100)                              
{
	m_pStateMachine = new StateMachine<EnemyTank>(this);
	m_pStateMachine->setCurrentState( DazeAndRest::getInstance() );
}

EnemyTank::~EnemyTank() { delete m_pStateMachine; }
							  
void EnemyTank::update() {
	m_pStateMachine->update();
}

StateMachine<EnemyTank>* EnemyTank::getFSM()const {
	return m_pStateMachine;
}

void EnemyTank::damageCalculaion(int damage) {
	m_HP -= damage;
}

int EnemyTank::getHP()const {
	return m_HP;
}

bool EnemyTank::isDying()const {
	if (m_HP <= DyingHP) { return true; }

	return false;
}