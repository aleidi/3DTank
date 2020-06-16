#include "AIController.h"
#include "GameCharacter.h"

AIController::AIController()
	:AIController(-1)
{
}

AIController::AIController(int id)
	:mID(id)
{
}

AIController::~AIController()
{
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

void AIController::setStateMachine(StateMachine<AIController>* new_StateMachine) {
	m_pStateMachine = new_StateMachine;
}

bool AIController::handleMessage(const Telegram& msg) {
	return m_pStateMachine->handleMessage(msg);
}