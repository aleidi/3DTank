#include "AIController.h"
#include "GameCharacter.h"
#include "EnemyTankOwnedStates.h" // :(
#include "BossOwnedStates.h"
#include "Pawn.h"
#include "Transform.h"
#include "EnemyTank.h"
#include "GameInstance.h"
#include "CollisionManager.h"
#include "EntityNames.h"

AIController::AIController()
	:AIController(-1)
{}

AIController::AIController(int id)
	:mID(id),mAccumulateRot(0),ControllerBase(-1)
{
 	m_pStateMachine = new StateMachine<AIController>(this);
  	m_pStateMachine->setCurrentState(Sleeep::getInstance());
	m_target = GameInstance::sGetInstance()->getPlayer();

}

AIController::~AIController()
{
	delete m_pStateMachine;
	m_pStateMachine = NULL;
}

void AIController::onStart()
{
}

void AIController::onUpdate(const float& deltaTime)
{
	m_pStateMachine->update(deltaTime);
	// MoveCharacter(Vector3::right * deltaTime);
}

void AIController::destroy()
{
	SceneManager::sGetInstance()->removeAIControllerFromPool(this);
}

void AIController::MoveCharacter(Vector3 value)
{
	reinterpret_cast<GameCharacter*>(mPawn)->Move(value);
}

bool AIController::handleMessage(const Telegram& msg) {
	return m_pStateMachine->handleMessage(msg);
}

void AIController::Attack(Vector3 battery_position, Vector3 direction, const int& tankType) {
	mPawn->attack(battery_position, direction, tankType);
}

void AIController::Attack(Vector3 battery_position, Vector3 direction, Pawn* target, const int& tankType) {
	mPawn->attack(battery_position, direction, target, tankType);
}

void AIController::Move(Vector3 force)
{
	reinterpret_cast<EnemyTank*>(mPawn)->move(force);
}

void AIController::Rotate(float x, float y, float z)
{
	mAccumulateRot = y;
	// mAccumulateRot = Math::lerp(mAccumulateRot, 0.0f, 0.999);

	mPawn->getTransform()->rotateY(mAccumulateRot);
}

void AIController::wakeup() {
	if (this->getFSM()->getCurrentState() == Sleeep::getInstance()) {
		if (this->getID() != ent_Tank_SuperEnemy)
			m_pStateMachine->changeState(Rest::getInstance());
		else
			m_pStateMachine->changeState(Alert::getInstance());
	}
}

void AIController::setTarget(Pawn* targetTank) {
	m_target = targetTank;
}

Pawn * AIController::getTarget()
{
	int targetID = -1;
	if ( !m_target->isAlive() ) {
		if (m_target == GameInstance::sGetInstance()->getPlayer())
		{
			return m_target;
		}
		if (m_target != GameInstance::sGetInstance()->getPlayer())
			targetID = this->getID();//reinterpret_cast<EnemyTank*>(m_target)->getAICtrl()->getID();
		targetID += 1;
		if(SceneManager::sGetInstance()->getAIController(targetID) != nullptr)
			setTarget(SceneManager::sGetInstance()->getAIController(targetID)->getPawn());
		else
			setTarget(GameInstance::sGetInstance()->getPlayer());
	}

	return m_target;
}
