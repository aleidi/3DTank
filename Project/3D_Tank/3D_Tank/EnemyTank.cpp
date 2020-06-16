#include "EnemyTank.h"
					

void EnemyTank::update() {
	m_pStateMachine->update();
}


void EnemyTank::setHP(int changeHP) {
	m_HP += changeHP;
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

bool EnemyTank::getHPRecovered()const {
	return this->m_HPRecovered;
}

void EnemyTank::setHPRecovered( bool isRecovered ) {
	this->m_HPRecovered = isRecovered;
}

bool EnemyTank::isEnemyInRange()const {
	if( Vector3::lengthSq( getPosPlayer, mTransform->getPosition() ) <= m_AttackRangeRadiusSq ) {
		// do something here to check if there are any obstacles
		// if no
		return true;
		// else return false;return true; 
	}
	return false;
}

bool EnemyTank::isLostEnemy()const {
	if (Vector3::lengthSq(getPosPlayer, mTransform->getPosition()) > m_PursuitRangeRadiusSq) {
		return true;
	}
	return false;
}