#pragma once
class EnemyTank;
class AIController;

class AITank
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

