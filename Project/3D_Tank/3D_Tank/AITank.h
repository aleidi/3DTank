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

	void changeTarget(int targetID);

private:
	EnemyTank* m_Tank;
	AIController* m_AICtrl;
};

