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

#define getTargetVelocity pEnemyTank->getTarget()->getVelocity()
#define getTargetSpeed pEnemyTank->getTarget()->getMaxSpeed()
#define getTargetPos pEnemyTank->getTarget()->getTransform()->getPosition()
#define getTargetHeading pEnemyTank->getTarget()->getTransform()->Forward

#define getPlayerSpeed	GameInstance::sGetInstance()->getPlayer()->getSpeed() /////////////////
#define getPlayerVelocity	GameInstance::sGetInstance()->getPlayer()->getVelocity() /////////////////

#define AITank reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())
#define getAIPos pEnemyTank->getPawn()->getTransform()->getPosition()
#define getAIHeading pEnemyTank->getPawn()->getTransform()->Forward
#define getAIVelocity  pEnemyTank->getPawn()->getVelocity()
//-------------------methods for Rest-------------------//
Rest* Rest::getInstance() {
	static Rest m_Rest;
	return &m_Rest;
}

void Rest::enter(AIController* pEnemyTank) {
	std::wstring wstr;
	wstr += std::to_wstring(AITank->getID()) + L"I'm going to rest. ";
	AITank->setHPRecovered(false);
	MessageBox(0, wstr.c_str(), 0, 0);
}

void Rest::execute(AIController* pEnemyTank, float deltaTime) {
	if (!AITank->getHPRecovered()) {
		AITank->setHPRecovered(true);
 		Dispatch->Dispatch_Message(ReplyInterval,
								   AITank->getID(),
								   AITank->getID(),
								   Msg_HPRecovered,
								   NO_ADDITIONAL_INFO);
	}

	////////////////////////changeState////////////////////////
	if (AITank->isEnemyInRange()) {
		if(AITank->isDying() )
			pEnemyTank->getFSM()->changeState(Evade::getInstance());
		else 
			pEnemyTank->getFSM()->changeState(Attack::getInstance());
	}

	if (AITank->getAttacked()) {
		AITank->setAttacked(false);
		if (AITank->isDying())
			pEnemyTank->getFSM()->changeState(Evade::getInstance());
		else
			pEnemyTank->getFSM()->changeState(Pursuit::getInstance());
	}

	if (AITank->getHP() == FullHP) {
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

void Wander::execute(AIController* pEnemyTank, float deltaTime) {
	float count = 0.0f;
	count += deltaTime;
	if (count > 0.0001) {
		count = 0;

		float disToBornSq = Vector3::lengthSq(getAIPos, AITank->getResetPoint());
		if ( disToBornSq > AITank->getWanderRangeRadiusSq() ) {
			Vector3 goBack = AITank->getResetPoint() - getAIPos;
			pEnemyTank->Move(goBack);
		}
		else {
			float jitterThisTimeSlice = AITank->getWanderJitter() * deltaTime;
			AITank->setWanderTarget(AITank->getWanderTarget() + Vector3(Math::RandomClamped() * jitterThisTimeSlice, 0,
				Math::RandomClamped() * jitterThisTimeSlice));
			AITank->setWanderTarget(AITank->getWanderTarget().normalize());
			AITank->setWanderTarget(AITank->getWanderTarget() * AITank->getWanderRadius());

			Vector3 forward = getAIHeading;
			Vector3 forward_normalize = forward.normalize();

			Vector3 target = AITank->getWanderTarget() + (forward_normalize * AITank->getWanderDistance());

			pEnemyTank->Move(target);
		}
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

void Avoidance::execute(AIController* pEnemyTank, float deltaTime) {

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

void Attack::execute(AIController* pEnemyTank, float deltaTime) {
	pEnemyTank->Attack();
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

void Evade::execute(AIController* pEnemyTank, float deltaTime) {
	float count = 0.0f;
	count += deltaTime;
	if (count > 0.0001) {
		count = 0.0f;
		Vector3 target = Vector3(0,0,0);
		Vector3 toPursuer = getTargetPos - getAIPos;

		float lookAheadTime = sqrt(Vector3::lengthSq(toPursuer, Vector3(0, 0, 0))) / (AITank->getMaxSpeed() + getTargetSpeed);
		Vector3 targetPos = getTargetPos + getTargetVelocity * lookAheadTime;
		Vector3 desiredVelocity = (getAIPos - targetPos).normalize() * AITank->getMaxSpeed();
		target = desiredVelocity - getAIVelocity;
		/////////////////////////beginning of movement/////////////////////////////
		pEnemyTank->Move(target);
	
		////////////////////////changeState////////////////////////
		/*
		if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->getAttacked()) {
			reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->setAttacked(false);
		}
		else if (!reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isEnemyInRange()) { // safe
			pEnemyTank->getFSM()->changeState(Rest::getInstance());
		}

		if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isObstacleHere()) {
			pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
		}

		if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->getHP() <= 0) {
			pEnemyTank->getFSM()->changeState(Death::getInstance());
		} */
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

void Pursuit::execute(AIController* pEnemyTank, float deltaTime) {
	float count = 0.0f;
	count += deltaTime;
	if (count > 0.0001) {
		count = 0.0f;

		Vector3 target = Vector3(0, 0, 0);
		Vector3 toEvader = getTargetPos - getAIPos;
		float relativeHeading = Vector3::dot(getAIHeading, getTargetHeading);
		
		if ((Vector3::dot(toEvader, getAIHeading) > 0) && (relativeHeading < -0.95)) { // acos(0.95)=18degs
			Vector3 targetPos = getTargetPos;
			Vector3 desiredVelocity = (targetPos - getAIPos).normalize() * AITank->getMaxSpeed();
			target = desiredVelocity - getAIVelocity;
		}
		
		else {
			/////////////////////////////////////////
			float lookAheadTime = sqrt(Vector3::lengthSq(toEvader, Vector3(0, 0, 0))) / (AITank->getMaxSpeed() + getTargetSpeed);
			float m_dot = Vector3::dot(getAIHeading, toEvader.normalize());
			const float coefficient = 0.005f;
			lookAheadTime += (m_dot - 1.0f) * -coefficient;

			/////////////////////////////////////////
			Vector3 targetPos = getTargetPos + (getTargetVelocity * lookAheadTime);
			Vector3 desiredVelocity = (targetPos - getAIPos).normalize() * AITank->getMaxSpeed();
			target = desiredVelocity - getAIVelocity;
		} 

		/////////////////////////beginning of movement/////////////////////////////
		pEnemyTank->Move(target);

		std::wstring wstr;
		wstr += L"velocity: (" + std::to_wstring(getAIVelocity.x) + L"," +
			std::to_wstring(getAIVelocity.y) + L"," +
			std::to_wstring(getAIVelocity.z) + L") \n";
		wstr += L"Target velocity: (" + std::to_wstring(getTargetVelocity.x) + L"," +
			std::to_wstring(getTargetVelocity.y) + L"," +
			std::to_wstring(getTargetVelocity.z) + L") \n";
		Engine::sGetInstance()->showtText(wstr.c_str(), 0, 0, 500, 500, true);
		////////////////////////changeState////////////////////////
		/*
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
		*/
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

void Death::execute(AIController* pEnemyTank, float deltaTime) {

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