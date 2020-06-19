#include "EnemyTankOwnedStates.h"
#include "State.h"
#include "EnemyTank.h"
#include "AIController.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"
#include "Engine.h"
#include <assert.h>

float count;
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

	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->getAttacked()) {
		reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->setAttacked(false);
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
			return true;
		}

		case Msg_IsAttacked: {
			MessageBox(0, L"nmsl(rest", 0, 0);
			reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->setAttacked(true);
			return true;
		}
							 
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
	float jitterThisTimeSlice = pEnemyTank->m_WanderJitter * pEnemyTank->deltaTime();
	pEnemyTank->m_WanderTarget += Vector3(Math::RandomClamped() * jitterThisTimeSlice, 0,
							  Math::RandomClamped() * jitterThisTimeSlice);
	pEnemyTank->m_WanderTarget = pEnemyTank->m_WanderTarget.normalize();
	pEnemyTank->m_WanderTarget = pEnemyTank->m_WanderTarget * pEnemyTank->m_WanderRadius;

	Vector3 forward = pEnemyTank->getPawn()->getTransform()->Forward;
	Vector3 forward_normalize = forward.normalize();
	Vector3 target = pEnemyTank->m_WanderTarget + (forward_normalize * pEnemyTank->m_WanderDistance );
  	Vector3 target_normalize = target.normalize();

	float dot = Vector3::dot(target_normalize, forward_normalize);
	dot = Math::Clamp(1.0f, -1.0f, dot );

	rotate = acosf(dot);
	rotate *= 180 / Pi;
	
	Vector3 acceleraion = target / mass;
	velocity += acceleraion * pEnemyTank->deltaTime();

	if (Vector3::lengthSq(velocity, Vector3(0, 0, 0)) > (pEnemyTank->maxspeed*pEnemyTank->maxspeed ) )
		velocity = velocity.normalize() * pEnemyTank->maxspeed;

	Vector3 newPos = velocity * pEnemyTank->deltaTime();

	pEnemyTank->Move(newPos);

	if(Vector3::lengthSq(velocity, Vector3(0, 0, 0)) > 0 )
		pEnemyTank->Rotate(0, rotate, 0);


	if (pEnemyTank->getID() == ent_Tank_Enemy) {
		std::wstring wstr;
		wstr += std::to_wstring(pEnemyTank->getID()) + L":_Tank X:" + std::to_wstring(pEnemyTank->getPawn()->getTransform()->getPosition().x);
		wstr += +L"_Tank Z:" + std::to_wstring(pEnemyTank->getPawn()->getTransform()->getPosition().z);
		wstr += +L"_Tank Vtarget: ( " + std::to_wstring(target.x) + L"," + std::to_wstring(target.y) + L"," + std::to_wstring(target.z);
		Engine::sGetInstance()->showtText(wstr.c_str(), 0, 0, 500, 500, true);
	}
	/*if (pEnemyTank->getID() == ent_Tank_SuperEnemy) {
		std::wstring wstr2;
		wstr2 += L"\n\n\n\n";	
		wstr2 += std::to_wstring(pEnemyTank->getID()) + L":_Tank X:" + std::to_wstring(pEnemyTank->getPawn()->getTransform()->getPosition().x);
		wstr2 += +L"_Tank Z:" + std::to_wstring(pEnemyTank->getPawn()->getTransform()->getPosition().z);
		wstr2 += +L"_Tank Vtarget: ( " + std::to_wstring(target.x) + L"," + std::to_wstring(target.y) + L"," + std::to_wstring(target.z);
		Engine::sGetInstance()->showtText(wstr2.c_str(), 0, 0, 500, 500, true);
	}*/
	/*
	timer += pEnemyTank->deltaTime();
	if (timer > 0.5) {
		timer = 0;
		pEnemyTank->Rotate(0, rotate, 0);
		pEnemyTank->Move(target);
	}
	else { pEnemyTank->Move(forward*0.001); }
	*/
	/*
	count += 0.01f;

	if (count > 50)
	{
		pEnemyTank->Rotate(0, 30* Math::RandomClamped(), 0);
		count = 0;
	}
	*/
	/*
	timer += pEnemyTank->deltaTime();
	if (timer > 10) {
		rotate = Math::RandomClamped() * 15;
		timer = 0;
		pEnemyTank->Rotate(0, rotate, 0);
	}
	
	Vector3 target = pEnemyTank->getPawn()->getTransform()->Forward * 0.0001f;
	*/
	
	////////////////////////changeState////////////////////////
	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isEnemyInRange()) {
		// pEnemyTank->getFSM()->changeState(Attack::getInstance());
	}

	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isObstacleHere()) {
		pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
	}

	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->getAttacked()) {
		reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->setAttacked(false);
		pEnemyTank->getFSM()->changeState(Pursuit::getInstance());
	}
	
}

void Wander::exit(AIController* pEnemyTank) {
	MessageBox(0, L"I stopped finding bad guy.(wander) ", 0, 0);
}

bool Wander::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	switch (msg.Msg) {
		case Msg_IsAttacked: {
			MessageBox(0, L"nmsl(wander", 0, 0);
			reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->setAttacked(true);
		}

		return true;
	}
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
	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->getAttacked()) {
		reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->setAttacked(false);
	}
	else if (!reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isEnemyInRange() ) { // safe
		pEnemyTank->getFSM()->changeState(Rest::getInstance());
	}

	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isObstacleHere()) {
		pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
	} 

	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->getHP() <= 0) {
		pEnemyTank->getFSM()->changeState(Death::getInstance());
	}
}

void Evade::exit(AIController* pEnemyTank) {
	MessageBox(0, L"I stopped running away. ", 0, 0);
}

bool Evade::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	switch (msg.Msg) {
	case Msg_IsAttacked: {
		MessageBox(0, L"nmsl(evade", 0, 0);
		reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->setAttacked(true);
	}

	return true;
	}
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

//-------------------methods for Death-------------------//
Death* Death::getInstance() {
	static Death m_Death;
	return &m_Death;
}

void Death::enter(AIController* pEnemyTank) {
	MessageBox(0, L"awsl", 0, 0);
}

void Death::execute(AIController* pEnemyTank) {

	MessageBox(0, L"BOW! I DEAD", 0, 0);
	////////////////////////changeState////////////////////////
	// Dead is end//
}

void Death::exit(AIController* pEnemyTank) {
	MessageBox(0, L"slsl", 0, 0);
}

bool Death::onMessage(AIController* pEnemyTank, const Telegram& msg) {
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