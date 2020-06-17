#include "EnemyTank.h"
/*
void EnemyTank::update() {
	m_pStateMachine->update();
}
*/

EnemyTank::EnemyTank(int ID)
	:mAttribute({95,1000.0f,2000.0f}),
	m_HPRecovered(false),
	BaseGameEntity(ID)
{
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBattery", L"Tank\\TankTex");
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBody", L"Tank\\TankTex");
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankTrack_L", L"Tank\\TankTrack");
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankTrack_R", L"Tank\\TankTrack");

	mTransform->setScale(0.002f, 0.002f, 0.002f);
	// m_pStateMachine = new StateMachine<EnemyTank>(this);
	// m_pStateMachine->setCurrentState(Rest::getInstance());
}


void EnemyTank::setHP(int changeHP) {
	mAttribute.HP += changeHP;
}

int EnemyTank::getHP()const {
	return mAttribute.HP;
}

/*
bool EnemyTank::handleMessage(const Telegram& msg) {
	return m_pStateMachine->handleMessage(msg); 
}
*/

bool EnemyTank::isDying()const {
	if (mAttribute.HP <= DyingHP) {
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
	if( Vector3::lengthSq( getPosPlayer, mTransform->getPosition() ) <= mAttribute.AttackRangeRadiusSq ) {
		// do something here to check if there are any obstacles
		// if no
		return true;
		// else return false;return true; 
	}
	return false;
}

bool EnemyTank::isLostEnemy()const {
	if (Vector3::lengthSq(getPosPlayer, mTransform->getPosition()) > mAttribute.PursuitRangeRadiusSq) {
		return true;
	}
	return false;
}