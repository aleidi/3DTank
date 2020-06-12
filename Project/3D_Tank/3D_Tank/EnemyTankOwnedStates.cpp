#include "EnemyTankOwnedStates.h"
#include "State.h"
#include "EnemyTank.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"

//-------------------methods for Rest-------------------//

Rest* Rest::getInstance() {
	static Rest m_Rest;
	return &m_Rest;
}

void Rest::enter(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I'm going to rest. ", 0, 0);
}

void Rest::execute(EnemyTank* pEnemyTank) {
	if (!pEnemyTank->getHPRecovered()) {
		pEnemyTank->setHPRecovered(true);
 		Dispatch->Dispatch_Message(10,
								   pEnemyTank->getID(),
								   pEnemyTank->getID(),
								   Msg_HPRecovered,
								   NO_ADDITIONAL_INFO);
	}

	////////////////////////changeState////////////////////////
	if (pEnemyTank->isEnemyInRange()) {
		if( pEnemyTank->isDying() )
			pEnemyTank->getFSM()->changeState(Evade::getInstance());
		else 
			pEnemyTank->getFSM()->changeState(Attack::getInstance());
	}

	if (pEnemyTank->isAttacked()) {
		if (pEnemyTank->isDying())
			pEnemyTank->getFSM()->changeState(Evade::getInstance());
		else
			pEnemyTank->getFSM()->changeState(Pursuit::getInstance());
	}

	if (pEnemyTank->getHP() == FullHP) {
		pEnemyTank->getFSM()->changeState(Wander::getInstance());
	}

}

void Rest::exit(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I stopped resting. ", 0, 0);
}

bool Rest::onMessage(EnemyTank* pEnemyTank, const Telegram& msg) {
	switch (msg.Msg) {
		case Msg_HPRecovered: {
			pEnemyTank->setHP(5);
			MessageBox(0, L"HP+5 ", 0, 0);
			pEnemyTank->setHPRecovered(false);
		}
		return true;
	}
	return false;
}

//-------------------methods for Wander-------------------//
Wander* Wander::getInstance() {
	static Wander m_Wander;
	return &m_Wander;
}

void Wander::enter(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I'm going to find bad guy.(Wander) ", 0, 0);
}

void Wander::execute(EnemyTank* pEnemyTank) {
	if (pEnemyTank->isEnemyInRange()) {
		pEnemyTank->getFSM()->changeState(Attack::getInstance());
	}

	if (pEnemyTank->isObstacleHere()) {
		pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
	}

	if (pEnemyTank->isAttacked()) {
		pEnemyTank->getFSM()->changeState(Pursuit::getInstance());
	}
}

void Wander::exit(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I stopped finding bad guy.(wander) ", 0, 0);
}

bool Wander::onMessage(EnemyTank* pEnemyTank, const Telegram& msg) {
	return false;
}

//-------------------methods for Avoidance-------------------//
Avoidance* Avoidance::getInstance() {
	static Avoidance m_Avoidance;
	return &m_Avoidance;
}

void Avoidance::enter(EnemyTank* pEnemyTank) {
	MessageBox(0, L"There is a f cking obstacle. ", 0, 0);
}

void Avoidance::execute(EnemyTank* pEnemyTank) {
	if (!pEnemyTank->isObstacleHere()) {
		pEnemyTank->getFSM()->revertToPerviousState();
	}
}

void Avoidance::exit(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I avoided the damn obstacle. ", 0, 0);
}

bool Avoidance::onMessage(EnemyTank* pEnemyTank, const Telegram& msg) {
	return false;
}


//-------------------methods for Attack-------------------//
Attack* Attack::getInstance() {
	static Attack m_Attack;
	return &m_Attack;
}

void Attack::enter(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I'm going to kick ur ass. ", 0, 0);
}

void Attack::execute(EnemyTank* pEnemyTank) {
	if (pEnemyTank->isDying()) {
		pEnemyTank->getFSM()->changeState(Evade::getInstance());
	}

	if (!pEnemyTank->isEnemyInRange()) {
		pEnemyTank->getFSM()->changeState(Pursuit::getInstance());
	}
}

void Attack::exit(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I stopped kicking ur ass. ", 0, 0);
}

bool Attack::onMessage(EnemyTank* pEnemyTank, const Telegram& msg) {
	return false;
}

//-------------------methods for Evade-------------------//
Evade* Evade::getInstance() {
	static Evade m_Evade;
	return &m_Evade;
}

void Evade::enter(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I'm going to run away. ", 0, 0);
}

void Evade::execute(EnemyTank* pEnemyTank) {
	if (!pEnemyTank->isEnemyInRange() && !pEnemyTank->isAttacked()) { // safe
		pEnemyTank->getFSM()->changeState(Rest::getInstance());
	}

	if (pEnemyTank->isObstacleHere()) {
		pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
	}
}

void Evade::exit(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I stopped running away. ", 0, 0);
}

bool Evade::onMessage(EnemyTank* pEnemyTank, const Telegram& msg) {
	return false;
}

//-------------------methods for Pursuit-------------------//
Pursuit* Pursuit::getInstance() {
	static Pursuit m_Pursuit;
	return &m_Pursuit;
}

void Pursuit::enter(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I'm chasing that damn bad guy.", 0, 0);
}

void Pursuit::execute(EnemyTank* pEnemyTank) {
	if (pEnemyTank->isObstacleHere()) {
		pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
	}

	if (pEnemyTank->isEnemyInRange()) {
		pEnemyTank->getFSM()->changeState(Attack::getInstance());
	}

	if (pEnemyTank->isDying()) {
		pEnemyTank->getFSM()->changeState(Evade::getInstance());
	}

	// if ( give up chasing for some reason  ) { pEnemyTank->getFSM()->changeState(Rest::getInstance()); }
}

void Pursuit::exit(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I stopped chasing.", 0, 0);
}

bool Pursuit::onMessage(EnemyTank* pEnemyTank, const Telegram& msg) {
	return false;
}






















//-------------------methods for Patrol-------------------//
Patrol* Patrol::getInstance() {
	static Patrol m_Patrol;
	return &m_Patrol;
}

void Patrol::enter(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I'm going to find bad guy. ", 0, 0);
}

void Patrol::execute(EnemyTank* pEnemyTank) {

}

void Patrol::exit(EnemyTank* pEnemyTank) {
	MessageBox(0, L"I stopped finding bad guy. ", 0, 0);
}

bool Patrol::onMessage(EnemyTank* pEnemyTank, const Telegram& msg) {
	return false;
}

