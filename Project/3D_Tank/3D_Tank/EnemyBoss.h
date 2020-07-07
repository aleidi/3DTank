#pragma once
#include "EnemyTank.h"

class EnemyBoss : public EnemyTank
{
public:
	enum Mode
	{
		Normal = 0,
		Super = 1
	};
public:
	EnemyBoss(int id);
	~EnemyBoss();

	void showUI(bool value);
	void ChangeMode(Mode mode);
	void onLateUpdate(float deltaTime) override;
	void onUpdate(float deltaTime) override;

private:
	GameObject* mNormalModel;
	GameObject* mSuperModel;

	UIImage* mImage;
	UIImage* mFrame;
	UIText* mName;

	float mOffset;
};

