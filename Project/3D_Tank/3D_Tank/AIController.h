#pragma once
#include "ControllerBase.h"
#include "StateMachine.h"

class AIController : public ControllerBase
{
public:
	AIController();
	AIController(int id);
	virtual ~AIController();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;

	virtual void MoveCharacter(Vector3 value);
	//////////////////////////////////////////////

	void setStateMachine(StateMachine<AIController>* new_StateMachine);
	StateMachine<AIController>* getFSM() const { return m_pStateMachine; }
	bool handleMessage(const Telegram& msg);

private:
	int mID;
	StateMachine<AIController>* m_pStateMachine;
};
