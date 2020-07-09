#include "CollisionManager.h"
#include "BossOwnedStates.h"
#include "EnemyTankOwnedStates.h"
#include "State.h"
#include "EnemyBoss.h"
#include "AIController.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"
#include "Math.h"
#include <assert.h>

#include "Engine.h"

#define getTargetVelocity pBoss->getTarget()->getVelocity()
#define getTargetSpeed pBoss->getTarget()->getMaxSpeed()
#define getTargetPos pBoss->getTarget()->getTransform()->getPosition()
#define getTargetHeading pBoss->getTarget()->getTransform()->Forward

#define BOSS reinterpret_cast<EnemyBoss*>(pBoss->getPawn())
#define getBOSSPos pBoss->getPawn()->getTransform()->getPosition()
#define getBOSSHeading pBoss->getPawn()->getTransform()->Forward
//-------------------methods for Alert-------------------//
Alert* Alert::getInstance() {
	static Alert m_Alert;
	return &m_Alert;
}

void Alert::enter(AIController* pBoss) {
	BOSS->setHPRecovered(false);
}

void Alert::execute(AIController* pBoss, float deltaTime) {
	if (!BOSS->getHPRecovered()) {
		BOSS->setHPRecovered(true);
		Dispatch->Dispatch_Message(BOSS->ReplyInterval,
									BOSS->getID(),
									BOSS->getID(),
									Msg_HPRecovered,
									NO_ADDITIONAL_INFO);
	}

	////////////////////////changeState////////////////////////
	if (BOSS->isEnemyInRange()) {
		if (BOSS->isDying())
			pBoss->getFSM()->changeState(Violent::getInstance());
		else
			pBoss->getFSM()->changeState(Battle::getInstance());
	}

	if (BOSS->getAttacked()) {
		BOSS->setAttacked(false);
		if (BOSS->isDying())
			pBoss->getFSM()->changeState(Violent::getInstance());
		else
			pBoss->getFSM()->changeState(Battle::getInstance());
	}

}

void Alert::exit(AIController* pBoss) {

}

bool Alert::onMessage(AIController* pBoss, const Telegram& msg) {
	switch (msg.Msg) {
	case Msg_HPRecovered: {
		if (BOSS->getHP() <= BOSS->FullHP) {
			BOSS->setHP(5);
			if(BOSS->getHP() > BOSS->FullHP)
				BOSS->setHP(BOSS->FullHP - BOSS->getHP());
		}
		BOSS->setHPRecovered(false);
		return true;
	}

	case Msg_IsAttacked: {
		BOSS->setAttacked(true);
		return true;
	}

	}
	return false;
}

//-------------------methods for Battle-------------------//
Battle* Battle::getInstance() {
	static Battle m_Battle;
	return &m_Battle;
}

void Battle::enter(AIController* pBoss) {
}

void Battle::execute(AIController* pBoss, float deltaTime) {
	////////////////////////////////////////////////////////////
	////     Similar to normal enemy tank attack state      ////
	////            missile every 3 normal shot           ////
	//// Wait for the attack state of enemytank to be fixed ////
	BOSS->aiCount += deltaTime;
	if (BOSS->aiCount > BOSS->attackTimeDelay()) {
		BOSS->aiCount = 0.0f;
		if (normalshot < 3) {
			pBoss->Attack(BOSS->batteryPosition(), getTargetPos - BOSS->batteryPosition() );  // + 01
			BOSS->rotateBattery(0, -offset, 0);
			normalshot += 1;
		}
		
		else { 
			BOSS->rotateBattery(0, -offset, 0);
			pBoss->Attack(BOSS->batteryPosition(), getBOSSHeading,pBoss->getTarget());  // + 01
			normalshot = 0;
		} 
	}
	////////////////////////Battery follows////////////////////////////
	Vector3 bossxzPos = getBOSSPos - Vector3(0, getBOSSPos.y, 0);
	Vector3 targetDirection = (getTargetPos - bossxzPos).normalize();
	float dot = Vector3::dot(targetDirection, getBOSSHeading);
	dot = Math::Clamp(1.0f, -1.0f, dot);
	float rotate = acosf(dot) * 180 / Pi;
	Vector3 cross = Vector3::cross(targetDirection, getBOSSHeading);
	if (cross.y > 0)
		rotate = -rotate;

	rotate = Math::Clamp(BOSS->maxTurnRate(), -1 * BOSS->maxTurnRate(), rotate);
	BOSS->getTransform()->rotate(0, rotate, 0);

	////////////////////////changeState/////////////////////////
	if (BOSS->getHP() <= BOSS->FullHP * 0.5 ) {
		pBoss->getFSM()->changeState(StageTwo::getInstance());
	}

}

void Battle::exit(AIController* pBoss) {

}

bool Battle::onMessage(AIController* pBoss, const Telegram& msg) {
	return false;
}

//-------------------methods for StageTwo-------------------//
StageTwo* StageTwo::getInstance() {
	static StageTwo m_StageTwo;
	return &m_StageTwo;
}

void StageTwo::enter(AIController* pBoss) {
	//MessageBox(0, L"fxck u", 0, 0);
	BOSS->enableFloat(true);
	BOSS->setSuperAttackInterval(3.0f);
}

void StageTwo::execute(AIController* pBoss, float deltaTime) {
	////////////////////////normal attack/////////////////////////////
	BOSS->aiCount += deltaTime;
	if (BOSS->aiCount > BOSS->attackTimeDelay() * 1.5 ) {
		BOSS->aiCount = 0.0f;
		if (normalshot < 2) {
			pBoss->Attack(BOSS->batteryPosition(), getTargetPos - BOSS->batteryPosition());  // + 01
			BOSS->rotateBattery(0, -offset, 0);
			normalshot += 1;
		}

		else {
			BOSS->rotateBattery(0, -offset, 0);
			pBoss->Attack(BOSS->batteryPosition(), getBOSSHeading, pBoss->getTarget());  // + 01
			normalshot = 0;
		}
	}
	////////////////////////Battery follows////////////////////////////
	Vector3 bossxzPos = getBOSSPos - Vector3(0, getBOSSPos.y, 0);
	Vector3 targetDirection = (getTargetPos - bossxzPos).normalize();
	float dot = Vector3::dot(targetDirection, getBOSSHeading);
	dot = Math::Clamp(1.0f, -1.0f, dot);
	float rotate = acosf(dot) * 180 / Pi;
	Vector3 cross = Vector3::cross(targetDirection, getBOSSHeading);
	if (cross.y > 0)
		rotate = -rotate;

	rotate = Math::Clamp(BOSS->maxTurnRate(), -1 * BOSS->maxTurnRate(), rotate);
	BOSS->getTransform()->rotate(0, rotate, 0);

	////////////////////////SuperAttack/////////////////////////
	superCount += deltaTime;
	if (superCount > 3.0f ) {
		if (particleSwitch) {
			BOSS->playSuperAttackParticle();
			particleSwitch = false;
		}

		if (superCount > 6.0f) {
			superCount = 0.0f;
			BOSS->preDoSuperAttack();
			BOSS->enableSuperAttack(true);
			particleSwitch = true;
		}
	}

	////////////////////////changeState/////////////////////////
	if (BOSS->isDying()) {
		pBoss->getFSM()->changeState(Violent::getInstance());
	}
}

void StageTwo::exit(AIController* pBoss) {

}

bool StageTwo::onMessage(AIController* pBoss, const Telegram& msg) {
	return false;
}

//-------------------methods for Violent-------------------//
Violent* Violent::getInstance() {
	static Violent m_Violent;
	return &m_Violent;
}

void Violent::enter(AIController* pBoss) {
	BOSS->initViolent(10, 10);
}

void Violent::execute(AIController* pBoss, float deltaTime) {
	////////////////////////SuperAttack/////////////////////////

	superCount += deltaTime;
	if (superCount > 3.0f) {
		if (particleSwitch) {
			BOSS->playSuperAttackParticle();
			particleSwitch = false;
		}

		if (superCount > 6.0f) {
			superCount = 0.0f;
			BOSS->preDoSuperAttack();
			BOSS->enableSuperAttack(true);
			particleSwitch = true;
		}
	}

	////////////////////////Battery follows////////////////////////////
	Vector3 bossxzPos = getBOSSPos - Vector3(0, getBOSSPos.y, 0);
	Vector3 targetDirection = (getTargetPos - bossxzPos).normalize();
	float dot = Vector3::dot(targetDirection, getBOSSHeading);
	dot = Math::Clamp(1.0f, -1.0f, dot);
	float rotate = acosf(dot) * 180 / Pi;
	Vector3 cross = Vector3::cross(targetDirection, getBOSSHeading);
	if (cross.y > 0)
		rotate = -rotate;

	rotate = Math::Clamp(BOSS->maxTurnRate(), -1 * BOSS->maxTurnRate(), rotate);
	BOSS->getTransform()->rotate(0, rotate, 0);


	////////////////////////changeState/////////////////////////
	if (BOSS->getHP() <= 0) {
		pBoss->getFSM()->changeState(Death::getInstance());
	}
}

void Violent::exit(AIController* pBoss) {
	BOSS->enableSuperAttack(false);
}

bool Violent::onMessage(AIController* pBoss, const Telegram& msg) {
	return false;
}