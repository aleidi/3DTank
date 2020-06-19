#pragma once
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
	// MessageBox(0, L"I stopped resting. ", 0, 0);
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
	// MessageBox(0, L"I'm going to find bad guy.(Wander) ", 0, 0);
}

void Wander::execute(AIController* pEnemyTank) {
	count += pEnemyTank->deltaTime();
	if (count > 0.001) {
		count = 0;

		float jitterThisTimeSlice = pEnemyTank->m_WanderJitter * pEnemyTank->deltaTime();
		pEnemyTank->m_WanderTarget += Vector3(Math::RandomClamped() * jitterThisTimeSlice, 0,
			Math::RandomClamped() * jitterThisTimeSlice);
		pEnemyTank->m_WanderTarget = pEnemyTank->m_WanderTarget.normalize();
		pEnemyTank->m_WanderTarget = pEnemyTank->m_WanderTarget * pEnemyTank->m_WanderRadius;

		Vector3 forward = pEnemyTank->getPawn()->getTransform()->Forward;
		Vector3 forward_normalize = forward.normalize();

		Vector3 target = pEnemyTank->m_WanderTarget + (forward_normalize * pEnemyTank->m_WanderDistance);

		// Vector3 target = Vector3(10, 0, 10);
		/////////////////////////beginning of movement/////////////////////////////
		Vector3 acceleraion = target / mass;
		pEnemyTank->velocity += acceleraion * pEnemyTank->deltaTime();

		if (Vector3::lengthSq(pEnemyTank->velocity, Vector3(0, 0, 0)) > (pEnemyTank->maxspeed*pEnemyTank->maxspeed))
			pEnemyTank->velocity = pEnemyTank->velocity.normalize() * pEnemyTank->maxspeed;

		Vector3 newPos = pEnemyTank->velocity * pEnemyTank->deltaTime();
		Vector3 newPos_normalize = target.normalize();

		float dot = Vector3::dot(pEnemyTank->velocity.normalize(), forward_normalize);
		dot = Math::Clamp(1.0f, -1.0f, dot);
		rotate = acosf(dot) * 180 / Pi;

		
		Vector3 cross = Vector3::cross(pEnemyTank->velocity.normalize(), forward_normalize);
		if (cross.y > 0) {
			rotate = -rotate;
		}
		


		// if(Vector3::lengthSq(velocity, Vector3(0, 0, 0)) > 0 )

		pEnemyTank->Move(newPos);

		if (rotate >= 1.0f || rotate <= -1.0f )
			pEnemyTank->Rotate(0, rotate, 0);


		std::wstring wstr;
		wstr += L"velocity: (" + std::to_wstring(pEnemyTank->velocity.normalize().x) + L"," +
			std::to_wstring(pEnemyTank->velocity.normalize().y) + L"," +
			std::to_wstring(pEnemyTank->velocity.normalize().z) + L") \n";
		wstr += L"forward: (" + std::to_wstring(forward_normalize.x) + L"," +
			std::to_wstring(forward_normalize.y) + L"," +
			std::to_wstring(forward_normalize.z) + L") \n";
		wstr += L"rotate: " + std::to_wstring(rotate);
		wstr += L",prerotate: " + std::to_wstring(prerotate);
		Engine::sGetInstance()->showtText(wstr.c_str(), 0, 0, 500, 500, true);

		/*
		pEnemyTank->Rotate(0, pEnemyTank->getID() * 90, 0);

		timer += pEnemyTank->deltaTime();
		if (timer > 3) {
			rotate = Math::RandomClamped() * 15;
			timer = 0;
			pEnemyTank->Rotate(0, rotate, 0);
		}
		*/
		// Vector3 abc = pEnemyTank->getPawn()->getTransform()->Forward * 0.0001f * ( pEnemyTank->getID() + 10 ) ;

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