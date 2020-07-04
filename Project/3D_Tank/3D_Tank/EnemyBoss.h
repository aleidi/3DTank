#pragma once
#include "EnemyTank.h"

class EnemyBoss : public EnemyTank
{
public:
	EnemyBoss(int id);
	~EnemyBoss();

	void showHP(bool value);

	void onLateUpdate(float deltaTime) override;

private:
	UIImage* mImage;
	UIImage* mFrame;
	UIText* mName;
	UIImage3D* mMagicCircle;
};

