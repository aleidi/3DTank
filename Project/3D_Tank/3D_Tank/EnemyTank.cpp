#include "EnemyTank.h"

EnemyTank::EnemyTank(int id) : BaseGameEntity(id),
							   m_HP(100)                              
{
	m_pStateMachine = new StateMachine<EnemyTank>(this);
	m_pStateMachine->setCurrentState( Rest::getInstance() );
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

bool EnemyTank::handleMessage(const Telegram& msg) {
	return m_pStateMachine->handleMessage(msg); 
}

bool EnemyTank::isDying()const {
	if (m_HP <= DyingHP) {
		return true;
	}

	return false;
}

bool EnemyTank::isEnemyFound()const {
	if( Vector3::lengthSq( getPosPlayer,m_Position ) <= m_AttackRangeRadiusSq ) {
		// do something here to check if there are any obstacles
		// if no
		return true;
		// else return false;return true; 
	}
	return false;
}