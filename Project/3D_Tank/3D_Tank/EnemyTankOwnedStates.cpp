#pragma once
#include "CollisionManager.h"
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
#include "Math.h"
#include <assert.h>

#define getTargetVelocity pEnemyTank->getTarget()->getVelocity()
#define getTargetSpeed pEnemyTank->getTarget()->getMaxSpeed()
#define getTargetPos pEnemyTank->getTarget()->getTransform()->getPosition()
#define getTargetHeading pEnemyTank->getTarget()->getTransform()->Forward

#define AITank reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())
#define getAIPos pEnemyTank->getPawn()->getTransform()->getPosition()
#define getAIHeading pEnemyTank->getPawn()->getTransform()->Forward
#define getAIVelocity  pEnemyTank->getPawn()->getVelocity()

//-------------------methods for Sleep-------------------//

Sleeep* Sleeep::getInstance() {
	static Sleeep m_Sleep;
	return &m_Sleep;
}

void Sleeep::enter(AIController* pEnemyTank) {

}

void Sleeep::execute(AIController* pEnemyTank, float deltaTime) {
	////////////////////////changeState////////////////////////
}

void Sleeep::exit(AIController* pEnemyTank) {

}

bool Sleeep::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	return false;
}

//-------------------methods for Rest-------------------//
Rest* Rest::getInstance() {
	static Rest m_Rest;
	return &m_Rest;
}

void Rest::enter(AIController* pEnemyTank) {
	std::wstring wstr;
	wstr += std::to_wstring(AITank->getID()) + L"I'm going to rest. ";
	AITank->setHPRecovered(false);
	// MessageBox(0, wstr.c_str(), 0, 0);
}

void Rest::execute(AIController* pEnemyTank, float deltaTime) {
	//std::wstring wstr;
	//wstr += std::to_wstring(getAIPos.x) + L"," + std::to_wstring(getAIPos.z);
	//MessageBox(0, wstr.c_str(), 0, 0);
	if (!AITank->getHPRecovered()) {
		AITank->setHPRecovered(true);
 		Dispatch->Dispatch_Message(AITank->ReplyInterval,
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

	if (AITank->getHP() >= AITank->FullHP) {
		AITank->setHP(AITank->FullHP - AITank->getHP());
		pEnemyTank->getFSM()->changeState(Wander::getInstance());
	}


	if (AITank->getHP() <= 0) {
		pEnemyTank->getFSM()->changeState(Death::getInstance());
	}
}

void Rest::exit(AIController* pEnemyTank) {
	//MessageBox(0, L"I stopped resting. ", 0, 0);
}

bool Rest::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	switch (msg.Msg) {
		case Msg_HPRecovered: {
			AITank->setHP(5);
			//MessageBox(0, L"HP+5 ", 0, 0);
			AITank->setHPRecovered(false);
			return true;
		}

		//case Msg_IsAttacked: {
		//	//MessageBox(0, L"nmsl(rest", 0, 0);
		//	AITank->setAttacked(true);
		//	return true;
		//}
		//					 
	}
	return false;
}

//-------------------methods for Wander-------------------//
Wander* Wander::getInstance() {
	static Wander m_Wander;
	return &m_Wander;
}

void Wander::enter(AIController* pEnemyTank) {
	//MessageBox(0, L"I'm going to find bad guy.(Wander) ", 0, 0);
}

void Wander::execute(AIController* pEnemyTank, float deltaTime) {
	if (pEnemyTank->getisPatrol())
		pEnemyTank->getFSM()->changeState(Patrol::getInstance());
	/////////////////////////////Patrol/////////////////////////////////
	else {
		AITank->aiCount += deltaTime;

		if (AITank->aiCount > 0.001f) {
			AITank->aiCount = 0.0f;

			float disToBornSq = Vector3::lengthSq(getAIPos, AITank->getResetPoint());
			if (disToBornSq > AITank->getWanderRangeRadiusSq()) {
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
			if (AITank->isEnemyInRange()) {
				pEnemyTank->getFSM()->changeState(Attack::getInstance());
			}

			if (AITank->isObstacleHere()) {
				pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
			}

			if (AITank->getAttacked()) {
				AITank->setAttacked(false);
				pEnemyTank->getFSM()->changeState(Pursuit::getInstance());
			}

		}
	}
}

void Wander::exit(AIController* pEnemyTank) {
	//MessageBox(0, L"I stopped finding bad guy.(Wander) ", 0, 0);
}

bool Wander::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	/*
	switch (msg.Msg) {
		case Msg_IsAttacked: {
			//MessageBox(0, L"nmsl(wander", 0, 0);
			AITank->setAttacked(true);
		}

		return true;
	}*/
	return false;

}

//-------------------methods for Patrol-------------------//
Patrol* Patrol::getInstance() {
	static Patrol m_Patrol; 
	return &m_Patrol;
}

void Patrol::enter(AIController* pEnemyTank) {
	pEnemyTank->toPatrolStart = !pEnemyTank->toPatrolEnd;
	// MessageBox(0, L"I'm going to find bad guy.(Patrol) ", 0, 0);
}

void Patrol::execute(AIController* pEnemyTank, float deltaTime) {
	AITank->aiCount += deltaTime;

	std::wstring wstr;

	if (AITank->aiCount > 0.001f) {
		Vector3 target = Vector3(0, 0, 0);
		AITank->aiCount = 0.0f;
		if (pEnemyTank->toPatrolEnd) {
			Vector3 targetPos = pEnemyTank->getPatrolEnd();
			Vector3 desiredVelocity = ( targetPos - getAIPos ).normalize() * AITank->getMaxSpeed();
			target = desiredVelocity - getAIVelocity;
			pEnemyTank->Move(target);
			//wstr += L"to end";
			//Engine::sGetInstance()->showtText(wstr.c_str(), 0, 0, 300, 300, true);
			if (Vector3::lengthSq(getAIPos, pEnemyTank->getPatrolEnd()) < 1) {
				pEnemyTank->toPatrolEnd = false;
				pEnemyTank->toPatrolStart = true;
			}
		}
		else if (pEnemyTank->toPatrolStart) {
			Vector3 targetPos = pEnemyTank->getPatrolStart();
			Vector3 desiredVelocity = (	targetPos - getAIPos ).normalize() * AITank->getMaxSpeed();
			target = desiredVelocity - getAIVelocity;
			pEnemyTank->Move(target);
			//wstr += L"to start";
			//Engine::sGetInstance()->showtText(wstr.c_str(), 0, 0, 300, 300, true);
			if ( Vector3::lengthSq( getAIPos, pEnemyTank->getPatrolStart()) < 1)  {
				pEnemyTank->toPatrolStart = false;
				pEnemyTank->toPatrolEnd = true;
			}
		}
		/////////////////////////beginning of movement/////////////////////////////
		
		//pEnemyTank->Move(target);
		
		////////////////////////changeState////////////////////////
		if (AITank->isEnemyInRange()) {
			pEnemyTank->getFSM()->changeState(Attack::getInstance());
		}

		if (AITank->isObstacleHere()) {
			pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
		}

		if (AITank->getAttacked()) {
			AITank->setAttacked(false);
			pEnemyTank->getFSM()->changeState(Pursuit::getInstance());
		}
	}
}

void Patrol::exit(AIController* pEnemyTank) {
	// MessageBox(0, L"I'm stop finding bad guy.(Patrol) ", 0, 0);
}

bool Patrol::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	switch (msg.Msg) {
	case Msg_IsAttacked: {
		//MessageBox(0, L"nmsl(wander", 0, 0);
		AITank->setAttacked(true);
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
	//MessageBox(0, L"There is a f cking obstacle. ", 0, 0);
}

void Avoidance::execute(AIController* pEnemyTank, float deltaTime) {
	Vector3 feelersForward = getAIHeading;
	Vector3 feelersRight = (getAIHeading + pEnemyTank->getPawn()->getTransform()->Right).normalize();
	Vector3 feelersLeft = (getAIHeading + pEnemyTank->getPawn()->getTransform()->Right * -1).normalize();
	Vector3 target = Vector3::zero;

	if (AITank->isObstacleForward()) {
		if (AITank->isObstacleRight()) {
			target = feelersLeft * AITank->getMaxSpeed() * 10.0f;
		}

		else if (AITank->isObstacleLeft()) {
			target = feelersRight * AITank->getMaxSpeed() * 10.0f;
		}

		else {
			target = getAIHeading * AITank->getMaxSpeed() * -10.0f;
		}
	}
	
	else if (AITank->isObstacleRight()) {
		target = feelersLeft * AITank->getMaxSpeed() * 10.0f;
	}

	else if (AITank->isObstacleLeft()) {
		target = feelersRight * AITank->getMaxSpeed() * 10.0f;
	}

	pEnemyTank->Move(target);
	////////////////////////changeState////////////////////////
	if (!AITank->isObstacleHere()) {
		pEnemyTank->getFSM()->revertToPerviousState();
	}
}

void Avoidance::exit(AIController* pEnemyTank) {
	//MessageBox(0, L"I avoided the damn obstacle. ", 0, 0);
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
	// MessageBox(0, L"I'm going to kick ur ass. ", 0, 0);
	pEnemyTank->Move(Vector3(0,0,0));
}

void Attack::execute(AIController* pEnemyTank, float deltaTime) {
	if (AITank->aiCount > AITank->attackTimeDelay()) {
		AITank->aiCount = 0.0f;
	/*
		GameObject* pTarget;
		bool isHit = CollisionManager::sGetInstance()->rayCheckWithTank(AITank->batteryPosition(),
																		AITank->batteryForward(),
																		sqrt(Vector3::lengthSq(getTargetPos, AITank->batteryPosition())) + 10.0f,
																		&pTarget);
	*/
	//	if( !isHit)
		pEnemyTank->Attack(AITank->batteryPosition(), AITank->batteryForward());
		AITank->playAttackParticle();
	//	else;
	} 
	//////////////////////////////////////////////////////////////////////
	Vector3 targetDirection = (getTargetPos - getAIPos).normalize();
	float dot = Vector3::dot(targetDirection, AITank->batteryForward());
	dot = Math::Clamp(1.0f, -1.0f, dot);
	float rotate = acosf(dot) * 180 / Pi;
	Vector3 cross = Vector3::cross(targetDirection, AITank->batteryForward());
	if (cross.y > 0)
		rotate = -rotate;


	AITank->rotateBattery(0, rotate, 0);

	AITank->aiCount += deltaTime;
	if (AITank->aiCount > AITank->attackTimeDelay()) {    // AITank->attackTimeDelay()
		int hitRate = AITank->hitRate();
		if (0 == rand() % hitRate);
		else {
			AITank->rotateBattery(0, Math::RandomClamped() * AITank->offset(), 0);
				// pEnemyTank->Attack(AITank->batteryPosition(), AITank->batteryForward());
		}
	}

	////////////////////////changeState////////////////////////
	if (AITank->isDying()) {
		pEnemyTank->getFSM()->changeState(Evade::getInstance());
	}

	if (!AITank->isEnemyInRange()) {
		pEnemyTank->getFSM()->changeState(Pursuit::getInstance());
	}
}

void Attack::exit(AIController* pEnemyTank) {
	//MessageBox(0, L"I stopped kicking ur ass. ", 0, 0);
		float dot = Vector3::dot(getAIHeading, AITank->batteryForward());
		dot = Math::Clamp(1.0f, -1.0f, dot);
		float rotate = acosf(dot) * 180 / Pi;
		Vector3 cross = Vector3::cross(getAIHeading, AITank->batteryForward());
		if (cross.y > 0)
			rotate = -rotate;

		// rotate = Math::Clamp(AITank->maxTurnRate(), -1 * AITank->maxTurnRate(), rotate);
		AITank->rotateBattery(0, rotate, 0);
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
	//MessageBox(0, L"I'm going to run away. ", 0, 0);
}

void Evade::execute(AIController* pEnemyTank, float deltaTime) {
	AITank->aiCount += deltaTime;
	if (AITank->aiCount > 0.001) {
		AITank->aiCount = 0.0f;
		Vector3 target = Vector3(0,0,0);
		Vector3 toPursuer = getTargetPos - getAIPos;

		float lookAheadTime = sqrt(Vector3::lengthSq(toPursuer, Vector3(0, 0, 0))) / (AITank->getMaxSpeed() + getTargetSpeed);
		Vector3 targetPos = getTargetPos + getTargetVelocity * lookAheadTime;
		Vector3 desiredVelocity = (getAIPos - targetPos).normalize() * AITank->getMaxSpeed();
		target = desiredVelocity - getAIVelocity;
		/////////////////////////beginning of movement/////////////////////////////
		pEnemyTank->Move(target);
	
		////////////////////////changeState////////////////////////
		
		if (AITank->getAttacked()) {
			AITank->setAttacked(false);
		}
		else if (!AITank->isEnemyInRange()) { // safe
			pEnemyTank->getFSM()->changeState(Rest::getInstance());
		}

		if (AITank->isObstacleHere()) {
			pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
		}

		if (AITank->getHP() <= 0) {
			pEnemyTank->getFSM()->changeState(Death::getInstance());
		} 
	}
}

void Evade::exit(AIController* pEnemyTank) {
	//MessageBox(0, L"I stopped running away. ", 0, 0);
}

bool Evade::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	switch (msg.Msg) {
	case Msg_IsAttacked: {
		//MessageBox(0, L"nmsl(evade", 0, 0);
		AITank->setAttacked(true);
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
	//MessageBox(0, L"I'm chasing that damn bad guy.", 0, 0);
}

void Pursuit::execute(AIController* pEnemyTank, float deltaTime) {
	AITank->aiCount += deltaTime;
	if (AITank->aiCount > 0.001) {
		AITank->aiCount = 0.0f;

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
			const float coefficient = 0.05f;
			lookAheadTime += (m_dot - 1.0f) * -coefficient;

			/////////////////////////////////////////
			Vector3 targetPos = getTargetPos + (getTargetVelocity * lookAheadTime);
			Vector3 desiredVelocity = (targetPos - getAIPos).normalize() * AITank->getMaxSpeed();
			target = desiredVelocity - getAIVelocity;
		} 

		/////////////////////////beginning of movement/////////////////////////////
		pEnemyTank->Move(target);

		////////////////////////changeState////////////////////////
		
		if (AITank->isObstacleHere()) {
			pEnemyTank->getFSM()->changeState(Avoidance::getInstance());
		}

		if (AITank->isEnemyInRange()) {
			pEnemyTank->getFSM()->changeState(Attack::getInstance());
		}

		if (AITank->isDying()) {
			pEnemyTank->getFSM()->changeState(Evade::getInstance());
		}

		if (AITank->isLostEnemy() ) {
			pEnemyTank->getFSM()->changeState(Rest::getInstance());
		}
		
	}
}

void Pursuit::exit(AIController* pEnemyTank) {
	//MessageBox(0, L"I stopped chasing.", 0, 0);
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
	Dispatch->Dispatch_Message(1.0f,
		AITank->getID(),
		AITank->getID(),
		Msg_DeathDelay,
		NO_ADDITIONAL_INFO);

	//AITank->playDeathParticle();
	//MessageBox(0, L"awsl", 0, 0);
}

void Death::execute(AIController* pEnemyTank, float deltaTime) {

	//MessageBox(0, L"BOW! I DEAD", 0, 0);
	////////////////////////changeState////////////////////////
	// Dead is end//
}

void Death::exit(AIController* pEnemyTank) {
	//MessageBox(0, L"slsl", 0, 0);
}

bool Death::onMessage(AIController* pEnemyTank, const Telegram& msg) {
	switch (msg.Msg) {
	case Msg_DeathDelay: {
		AITank->playDeathParticle();
		return true;
	}

	}
	return false;
}
