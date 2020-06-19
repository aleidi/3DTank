#include "AIController.h"
#include "GameCharacter.h"
#include "EnemyTankOwnedStates.h" // :(
#include "Pawn.h"
#include "Transform.h"

AIController::AIController()
	:AIController(-1)
{}

AIController::AIController(int id)
	:mID(id),mAccumulateRot(0)
{
	float theta = Math::RandFloat() * 2 * Pi;
	m_WanderTarget = Vector3(m_WanderRadius * cos(theta), 0, m_WanderRadius * sin(theta));

	m_pStateMachine = new StateMachine<AIController>(this);
	m_pStateMachine->setCurrentState(Rest::getInstance());
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
	m_deltaTime = deltaTime;
	m_pStateMachine->update();
	// MoveCharacter(Vector3::right * deltaTime);
}

void AIController::MoveCharacter(Vector3 value)
{
	reinterpret_cast<GameCharacter*>(mPawn)->Move(value);
}

bool AIController::handleMessage(const Telegram& msg) {
	return m_pStateMachine->handleMessage(msg);
}

void AIController::Move(Vector3 force)
{
	mPawn->getTransform()->translate(force);
}

void AIController::Rotate(float x, float y, float z)
{
	mAccumulateRot = y;
	mAccumulateRot = Math::lerp(mAccumulateRot, 0.0f, 0.999);

	mPawn->getTransform()->rotateY(mAccumulateRot);
}
