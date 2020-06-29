#include "CollisionManager.h"
#include "BossOwnedStates.h"
#include "State.h"
#include "EnemyTank.h"
#include "AIController.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"
// #include "Engine.h"
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
		reinterpret_cast<EnemyTank*>(pBoss->getPawn())->setAttacked(true);
		return true;
	}

	}
	return false;
}


//-------------------methods for Attack-------------------//
Battle* Battle::getInstance() {
	static Battle m_Battle;
	return &m_Battle;
}

void Battle::enter(AIController* pBoss) {
	// MessageBox(0, L"I'm going to kick ur ass. ", 0, 0);
}

void Battle::execute(AIController* pBoss, float deltaTime) {
	Vector3 targetDirection = (getTargetPos - getAIPos).normalize();
	float dot = Vector3::dot(targetDirection, AITank->batteryForward());
	dot = Math::Clamp(1.0f, -1.0f, dot);
	float rotate = acosf(dot) * 180 / Pi;
	Vector3 cross = Vector3::cross(targetDirection, AITank->batteryForward());
	if (cross.y > 0)
		rotate = -rotate;

	if (rotate >= 1.0f || rotate <= -1.0f)
		AITank->rotateBattery(0, rotate, 0);

	count += deltaTime;
	if (count > 5.0f) {
		count = 0.0f;
		pEnemyTank->Attack(AITank->batteryPosition(), AITank->batteryForward());
	}

	////////////////////////changeState////////////////////////
	if (reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isDying()) {
		pEnemyTank->getFSM()->changeState(Evade::getInstance());
	}

	if (!reinterpret_cast<EnemyTank*>(pEnemyTank->getPawn())->isEnemyInRange()) {
		pEnemyTank->getFSM()->changeState(Pursuit::getInstance());
	}
}

void Battle::exit(AIController* pBoss) {
	//MessageBox(0, L"I stopped kicking ur ass. ", 0, 0);

	float dot = Vector3::dot(getAIHeading, AITank->batteryForward());
	dot = Math::Clamp(1.0f, -1.0f, dot);
	float rotate = acosf(dot) * 180 / Pi;
	Vector3 cross = Vector3::cross(getAIHeading, AITank->batteryForward());
	if (cross.y > 0)
		rotate = -rotate;

	if (rotate >= 1.0f || rotate <= -1.0f)
		AITank->rotateBattery(0, rotate, 0);
}

bool Battle::onMessage(AIController* pBoss, const Telegram& msg) {
	return false;
}
