#pragma once
#include "GameObject.h"
class EnemyTank;
class AIController;

class AITank : public GameObject
{
public:
	AITank(int ID);
	AITank(int ID, int targetID);
	~AITank();

	EnemyTank* getTank();
	AIController* getCtrl();
	int getID() { return m_ID; }

	void changeTarget(int targetID);

	bool isAlive();

private:
	EnemyTank* m_Tank;
	AIController* m_AICtrl;
	int m_ID;
};

