#pragma once
#include "ControllerBase.h"
#include "StateMachine.h"
#include "Pawn.h"

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

	void setTarget(AIController* targetTank) { m_target = targetTank; }
	AIController* getTarget() { return m_target; }

	void setWanderData(float r, float d, float j) {
		m_WanderRadius = r;
		m_WanderDistance = d;
		m_WanderJitter = j;
	}

	float m_WanderRadius;
	float m_WanderDistance;
	float m_WanderJitter;
	Vector3 m_WanderTarget;

private:
	int mID;
	float m_deltaTime;
	float mAccumulateRot;

	StateMachine<AIController>* m_pStateMachine;

	AIController* m_target;

};
