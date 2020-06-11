#include "EnemyTankOwnedStates.h"
#include "State.h"
#include "EnemyTank.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"

Vector3 posPlayer;
//-------------------methods for Rest-------------------//

Rest* Rest::getInstance() {
	static Rest* m_DazeAndRest;
	return m_DazeAndRest;
}

void Rest::enter(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I'm going to rest. ", 0, 0);
}

void Rest::execute(EnemyTank* pEnemyTank) {
	if (pEnemyTank->isEnemyFound(posPlayer)) {
		
	}

	
}

void Rest::exit(EnemyTank* pEnemyTank) {

}

bool Rest::onMessage(EnemyTank* agent, const Telegram& msg) {
	return false;
}

//-------------------methods for Patrol-------------------//
Patrol* Patrol::getInstance() {
	static Patrol* m_Patrol;
	return m_Patrol;
}

void Patrol::enter(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I'm going to Patrol. ", 0, 0);
}

void Patrol::execute(EnemyTank* pEnemyTank) {

}

void Patrol::exit(EnemyTank* pEnemyTank) {

}

bool Patrol::onMessage(EnemyTank* agent, const Telegram& msg) {
	return false;
}

//-------------------methods for Attack-------------------//
Attack* Attack::getInstance() {
	static Attack* m_Patrol;
	return m_Patrol;
}

void Attack::enter(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I'm going to kick ur ass. ", 0, 0);
}

void Attack::execute(EnemyTank* pEnemyTank) {

}

void Attack::exit(EnemyTank* pEnemyTank) {

}

bool Attack::onMessage(EnemyTank* agent, const Telegram& msg) {
	return false;
}

//-------------------methods for Escape-------------------//
Evade* Evade::getInstance() {
	static Evade* m_Patrol;
	return m_Patrol;
}

void Evade::enter(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I'm going to run away. ", 0, 0);
}

void Evade::execute(EnemyTank* pEnemyTank) {

}

void Evade::exit(EnemyTank* pEnemyTank) {

}

bool Evade::onMessage(EnemyTank* agent, const Telegram& msg) {
	return false;
}

//-------------------methods for Avoidance-------------------//
Avoidance* Avoidance::getInstance() {
	static Avoidance* m_Patrol;
	return m_Patrol;
}

void Avoidance::enter(EnemyTank* pEnemyTank) {

}

void Avoidance::execute(EnemyTank* pEnemyTank) {

}

void Avoidance::exit(EnemyTank* pEnemyTank) {

}

bool Avoidance::onMessage(EnemyTank* agent, const Telegram& msg) {
	return false;
}
