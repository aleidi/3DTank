#include "EnemyTankOwnedStates.h"
#include "State.h"
#include "EnemyTank.h"
#include "AIController.h"
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

void Rest::enter(AIController* pEnemyTank) {
	reinterpret_cast<EnemyTank*>(reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn()))->setHPRecovered(false);
	MessageBox(0, L"I'm going to rest. ", 0, 0);
}

void Rest::execute(AIController* pEnemyTank) {
	if (!reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->getHPRecovered()) {
		reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->setHPRecovered(true);
 		Dispatch->Dispatch_Message(ReplyInterval,
							       reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->getID(),
			                       reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->getID(),
								   Msg_HPRecovered,
								   NO_ADDITIONAL_INFO);
	}

	////////////////////////changeState////////////////////////
	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isEnemyInRange()) {
		if(reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isDying() )
			pEnemyTank->getFSM()->changeState(Evade::getInstance());
		else 
			pEnemyTank->getFSM()->changeState(Attack::getInstance());
	}

	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isAttacked()) {
		if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isDying())
			pEnemyTank->getFSM()->changeState(Evade::getInstance());
		else
			pEnemyTank->getFSM()->changeState(Pursuit::getInstance());
	}

	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->getHP() == FullHP) {
		pEnemyTank->getFSM()->changeState(Wander::getInstance());
	}

}

void Rest::exit(AIController* pEnemyTank) {
	MessageBox(0, L"I stopped resting. ", 0, 0);
}

bool Rest::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	switch (msg.Msg) {
		case Msg_HPRecovered: {
			reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->setHP(5);
			MessageBox(0, L"HP+5 ", 0, 0);
			reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->setHPRecovered(false);
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

void Wander::enter(AIController* pEnemyTank) {
	MessageBox(0, L"I'm going to find bad guy.(Wander) ", 0, 0);
}

void Wander::execute(AIController* pEnemyTank) {
	
	////////////////////////changeState////////////////////////
	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isEnemyInRange()) {
		pEnemyTank->getFSM()->changeState(Attack::getInstance());
	}

	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isObstacleHere()) {
		pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
	}

	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isAttacked()) {
		pEnemyTank->getFSM()->changeState(Pursuit::getInstance());
	}
	
}

void Wander::exit(AIController* pEnemyTank) {
	MessageBox(0, L"I stopped finding bad guy.(wander) ", 0, 0);
}

bool Wander::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	return false;
}

//-------------------methods for Avoidance-------------------//
Avoidance* Avoidance::getInstance() {
	static Avoidance m_Avoidance;
	return &m_Avoidance;
}

void Avoidance::enter(AIController* pEnemyTank) {
	MessageBox(0, L"There is a f cking obstacle. ", 0, 0);
}

void Avoidance::execute(AIController* pEnemyTank) {

	////////////////////////changeState////////////////////////
	if (!reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isObstacleHere()) {
		pEnemyTank->getFSM()->revertToPerviousState();
	}
}

void Avoidance::exit(AIController* pEnemyTank) {
	MessageBox(0, L"I avoided the damn obstacle. ", 0, 0);
}

bool Avoidance::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	return false;
}


//-------------------methods for Attack-------------------//
Attack* Attack::getInstance() {
	static Attack m_Attack;
	return &m_Attack;
}

void Attack::enter(AIController* pEnemyTank) {
	MessageBox(0, L"I'm going to kick ur ass. ", 0, 0);
}

void Attack::execute(AIController* pEnemyTank) {

	////////////////////////changeState////////////////////////
	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isDying()) {
		pEnemyTank->getFSM()->changeState(Evade::getInstance());
	}

	if (!reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isEnemyInRange()) {
		pEnemyTank->getFSM()->changeState(Pursuit::getInstance());
	}
}

void Attack::exit(AIController* pEnemyTank) {
	MessageBox(0, L"I stopped kicking ur ass. ", 0, 0);
}

bool Attack::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	return false;
}

//-------------------methods for Evade-------------------//
Evade* Evade::getInstance() {
	static Evade m_Evade;
	return &m_Evade;
}

void Evade::enter(AIController* pEnemyTank) {
	MessageBox(0, L"I'm going to run away. ", 0, 0);
}

void Evade::execute(AIController* pEnemyTank) {

	////////////////////////changeState////////////////////////
	if (!reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isEnemyInRange() && !reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isAttacked()) { // safe
		pEnemyTank->getFSM()->changeState(Rest::getInstance());
	}

	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isObstacleHere()) {
		pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
	}
}

void Evade::exit(AIController* pEnemyTank) {
	MessageBox(0, L"I stopped running away. ", 0, 0);
}

bool Evade::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	return false;
}

//-------------------methods for Pursuit-------------------//
Pursuit* Pursuit::getInstance() {
	static Pursuit m_Pursuit;
	return &m_Pursuit;
}

void Pursuit::enter(AIController* pEnemyTank) {
	MessageBox(0, L"I'm chasing that damn bad guy.", 0, 0);
}

void Pursuit::execute(AIController* pEnemyTank) {

	////////////////////////changeState////////////////////////
	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isObstacleHere()) {
		pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
	}

	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isEnemyInRange()) {
		pEnemyTank->getFSM()->changeState(Attack::getInstance());
	}

	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isDying()) {
		pEnemyTank->getFSM()->changeState(Evade::getInstance()); 
	}

	if ( reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isLostEnemy() ) {
		pEnemyTank->getFSM()->changeState(Rest::getInstance()); 
	}
}

void Pursuit::exit(AIController* pEnemyTank) {
	MessageBox(0, L"I stopped chasing.", 0, 0);
}

bool Pursuit::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	return false;
}




















/*

//-------------------methods for Patrol-------------------//
Patrol* Patrol::getInstance() {
	static Patrol m_Patrol;
	return &m_Patrol;
}

void Patrol::enter(AIController* pEnemyTank) {
	MessageBox(0, L"I'm going to find bad guy. ", 0, 0);
}

void Patrol::execute(AIController* pEnemyTank) {

}

void Patrol::exit(AIController* pEnemyTank) {
	MessageBox(0, L"I stopped finding bad guy. ", 0, 0);
}

bool Patrol::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	return false;
}

*/