#include "CollisionManager.h"
#include "BossOwnedStates.h"
#include "EnemyTankOwnedStates.h"
#include "State.h"
#include "EnemyTank.h"
#include "AIController.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"
#include "Math.h"
#include <assert.h>

#define getTargetVelocity pBoss->getTarget()->getVelocity()
#define getTargetSpeed pBoss->getTarget()->getMaxSpeed()
#define getTargetPos pBoss->getTarget()->getTransform()->getPosition()
#define getTargetHeading pBoss->getTarget()->getTransform()->Forward

#define BOSS reinterpret_cast<EnemyTank*>(pBoss->getPawn())
#define getBOSSPos pBoss->getPawn()->getTransform()->getPosition()

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
		Dispatch->Dispatch_Message(ReplyInterval,
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
		if (BOSS->getHP() <= FullHP) {
			BOSS->setHP(5);
			if(BOSS->getHP() > FullHP)
				BOSS->setHP(FullHP - BOSS->getHP());
		}
		//MessageBox(0, L"HP+5 ", 0, 0);
		BOSS->setHPRecovered(false);
		return true;
	}

	case Msg_IsAttacked: {
		//MessageBox(0, L"nmsl(rest", 0, 0);
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
	//MessageBox(0, L"awsl", 0, 0);
}

void Battle::execute(AIController* pBoss, float deltaTime) {
	////////////////////////////////////////////////////////////
	////     Similar to normal enemy tank attack state      ////
	////            missile every 3 normal shot           ////
	//// Wait for the attack state of enemytank to be fixed ////

	if (BOSS->aiCount > BOSS->attackTimeDelay()) {
		BOSS->aiCount = 0.0f;
		if (normalshot < 3) {
			pBoss->Attack(BOSS->batteryPosition(), BOSS->batteryForward());
			normalshot += 1;
		}

		else {
			MessageBox(0, L"bang!", 0, 0);
			normalshot = 0;
		}
	}
	////////////////////////Battery follows////////////////////////////
	Vector3 targetDirection = (getTargetPos - getBOSSPos).normalize();
	float dot = Vector3::dot(targetDirection, BOSS->batteryForward());
	dot = Math::Clamp(1.0f, -1.0f, dot);
	float rotate = acosf(dot) * 180 / Pi;
	Vector3 cross = Vector3::cross(targetDirection, BOSS->batteryForward());
	if (cross.y > 0)
		rotate = -rotate;

	rotate = Math::Clamp(BOSS->maxTurnRate(), -1 * BOSS->maxTurnRate(), rotate);
	BOSS->rotateBattery(0, rotate, 0);
	////////////////////////////////////////////////////////////////////

	BOSS->aiCount += deltaTime;
	if (BOSS->aiCount > BOSS->attackTimeDelay()) {    // AITank->attackTimeDelay()
		int hitRate = BOSS->hitRate();
		if (0 == rand() % hitRate);
		else {
			BOSS->rotateBattery(0, Math::RandomClamped() * BOSS->offset(), 0);
			// pEnemyTank->Attack(AITank->batteryPosition(), AITank->batteryForward());
		}
	}

	////////////////////////changeState/////////////////////////
	if (BOSS->isDying()) {
		pBoss->getFSM()->changeState(Violent::getInstance());
	}

	if (!BOSS->isEnemyInRange()) {
		pBoss->getFSM()->changeState(Alert::getInstance());
	}
}

void Battle::exit(AIController* pBoss) {

}

bool Battle::onMessage(AIController* pBoss, const Telegram& msg) {
	return false;
}

//-------------------methods for Violent-------------------//
Violent* Violent::getInstance() {
	static Violent m_Violent;
	return &m_Violent;
}

void Violent::enter(AIController* pBoss) {
	violentTime = 20.0f;
}

void Violent::execute(AIController* pBoss, float deltaTime) {
	if (violentTime >= 0.0f) {
		violentTime -= deltaTime;

		BOSS->rotateBattery(0, 0.1f, 0);
		BOSS->aiCount += deltaTime;
		if (BOSS->aiCount > BOSS->attackTimeDelay()*0.1) {
			pBoss->Attack(BOSS->batteryPosition(), BOSS->batteryForward());
			BOSS->aiCount = 0.0f;
		}
	} // stage 1

	else {
		Vector3 targetDirection = (getTargetPos - getBOSSPos).normalize();
		float dot = Vector3::dot(targetDirection, BOSS->batteryForward());
		dot = Math::Clamp(1.0f, -1.0f, dot);
		float rotate = acosf(dot) * 180 / Pi;
		Vector3 cross = Vector3::cross(targetDirection, BOSS->batteryForward());
		if (cross.y > 0)
			rotate = -rotate;

		rotate = Math::Clamp(0.5f, -0.5f, rotate);
		BOSS->rotateBattery(0, rotate, 0);

		BOSS->aiCount += deltaTime;
		if (BOSS->aiCount > BOSS->attackTimeDelay()*0.5) {  
			pBoss->Attack(BOSS->batteryPosition(), BOSS->batteryForward()); // missile
			BOSS->aiCount = 0.0f;
		}
	} // stage 2
	////////////////////////changeState////////////////////////
	if (BOSS->getHP() <= 0) {
		pBoss->getFSM()->changeState(Death::getInstance());
	}
}

void Violent::exit(AIController* pBoss) {

}

bool Violent::onMessage(AIController* pBoss, const Telegram& msg) {
	return false;
}