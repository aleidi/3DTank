#pragma once
#include "ControllerBase.h"
#include "StateMachine.h"

class AIController : public ControllerBase
{
public:
	AIController();
	virtual ~AIController();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;

	virtual void MoveCharacter(Vector3 value);
	//////////////////////////////////////////////

	void setStateMachine(StateMachine<Pawn>* new_StateMachine);
	StateMachine<Pawn>* getFSM() const { return m_pStateMachine; }
	bool handleMessage(const Telegram& msg);

private:
	StateMachine<Pawn>* m_pStateMachine;
};
