#pragma once
#include "EnemyTank.h"

class EnemyBoss : public EnemyTank
{
public:
	EnemyBoss(int id);
	~EnemyBoss();

	void showHP(bool value);

private:
	UIImage* mImage;
	UIImage* mFrame;
};

