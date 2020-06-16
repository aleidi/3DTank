#include "AIController.h"
#include "GameCharacter.h"
#include "EnemyTankOwnedStates.h" // :(
AIController::AIController()
	:AIController(-1)
{
}

AIController::AIController(int id)
	:mID(id)
{
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