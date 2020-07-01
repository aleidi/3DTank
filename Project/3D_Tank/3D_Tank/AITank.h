#pragma once
#include "GameObject.h"
class EnemyTank;
class AIController;

class AITank : public GameObject
{
public:
	AITank(int ID);
	~AITank();

	EnemyTank* getTank();
	AIController* getCtrl();

private:
	EnemyTank* m_Tank;
	AIController* m_AICtrl;
};

