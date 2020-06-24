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

	void Attack(Vector3 battery_position, Vector3 direction);
	void Move(Vector3 Force);
	void Rotate(float x, float y, float z);

	void setTarget(Pawn* targetTank) { m_target = targetTank; }
	Pawn* getTarget() { return m_target; }

private:
	int mID;
	float m_deltaTime;
	float mAccumulateRot;

	StateMachine<AIController>* m_pStateMachine;

	Pawn* m_target;

};
