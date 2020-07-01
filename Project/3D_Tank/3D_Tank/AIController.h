#pragma once
#include "ControllerBase.h"
#include "StateMachine.h"
#include "Pawn.h"
#include "AITank.h"

class AIController : public ControllerBase
{
public:
	AIController();
	AIController(int id);
	virtual ~AIController();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	void destroy() override;

	virtual void MoveCharacter(Vector3 value);
	//////////////////////////////////////////////
	int getID() { return mID; }
	StateMachine<AIController>* getFSM() const { return m_pStateMachine; }
	bool handleMessage(const Telegram& msg);

	void Attack(Vector3 battery_position, Vector3 direction);
	void Attack(Vector3 battery_position, Vector3 direction, Pawn* target);
	void Move(Vector3 Force);
	void Rotate(float x, float y, float z);

	void setTarget(Pawn* targetTank);
	Pawn* getTarget();


	void setPrefabs(AITank* prefab) { m_Prefabs = prefab; }
	AITank* getPrefabs() { return m_Prefabs; }

	GameObject* obj;

private:
	int mID;
	float m_deltaTime;
	float mAccumulateRot;

	StateMachine<AIController>* m_pStateMachine;

	Pawn* m_target;

	AITank* m_Prefabs;
};
