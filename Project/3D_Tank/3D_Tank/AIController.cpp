#include "AIController.h"
#include "GameCharacter.h"
#include "EnemyTankOwnedStates.h" // :(
#include "Pawn.h"
#include "Transform.h"
#include "EnemyTank.h"
#include "GameInstance.h"
#include "CollisionManager.h"

AIController::AIController()
	:AIController(-1)
{}

AIController::AIController(int id)
	:mID(id),mAccumulateRot(0)
{
	m_pStateMachine = new StateMachine<AIController>(this);
	m_pStateMachine->setCurrentState(Attack::getInstance());

	m_target = GameInstance::sGetInstance()->getPlayer();
}

AIController::~AIController()
{
	delete m_pStateMachine;
}

void AIController::onStart()
{
}

void AIController::onUpdate(float deltaTime)
{
	m_pStateMachine->update(deltaTime);
	// MoveCharacter(Vector3::right * deltaTime);
}

void AIController::MoveCharacter(Vector3 value)
{
	reinterpret_cast<GameCharacter*>(mPawn)->Move(value);
}

bool AIController::handleMessage(const Telegram& msg) {
	return m_pStateMachine->handleMessage(msg);
}

void AIController::Attack(Vector3 battery_position, Vector3 direction) {
	mPawn->attack(battery_position, direction);
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
