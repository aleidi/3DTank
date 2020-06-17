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
	int getID() { return mID; }
	StateMachine<AIController>* getFSM() const { return m_pStateMachine; }
	bool handleMessage(const Telegram& msg);

	float deltaTime() { return m_deltaTime; }
	void Move(Vector3 Force);
	void Rotate(float x, float y, float z);

private:
	int mID;
	float m_deltaTime;
	StateMachine<AIController>* m_pStateMachine;
};
