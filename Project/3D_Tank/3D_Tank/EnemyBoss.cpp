#include "EnemyBoss.h"
#include "UIHP.h"

EnemyBoss::EnemyBoss(int id)
{
	mAttribute.FullHP = 100;
	mAttribute.m_HP = 100;

	m_ID = id;
	SceneManager::sGetInstance()->createModel(*this, "Boss/RedBaronN/m0_Arm_Base_Color", L"Boss/RedBaronN/Arm_Base_Color");
	SceneManager::sGetInstance()->createModel(*this, "Boss/RedBaronN/m1_Body_Base_Color", L"Boss/RedBaronN/Body_Base_Color");
	SceneManager::sGetInstance()->createModel(*this, "Boss/RedBaronN/m2_Chest_Base_Color", L"Boss/RedBaronN/Chest_Base_Color");
	SceneManager::sGetInstance()->createModel(*this, "Boss/RedBaronN/m3_Fire", L"Boss/RedBaronN/Fire");
	SceneManager::sGetInstance()->createModel(*this, "Boss/RedBaronN/m4_HeadHigh_Base_Color", L"Boss/RedBaronN/HeadHigh_Base_Color");
	SceneManager::sGetInstance()->createModel(*this, "Boss/RedBaronN/m5_Leg_Base_Color", L"Boss/RedBaronN/Leg_Base_Color");
	SceneManager::sGetInstance()->createModel(*this, "Boss/RedBaronN/m6_Sholder_Base_Color", L"Boss/RedBaronN/Sholder_Base_Color");
	SceneManager::sGetInstance()->createModel(*this, "Boss/RedBaronN/m7_SubArm_Base_Color", L"Boss/RedBaronN/SubArm_Base_Color");

	mTransform->setScale(0.5f, 0.5f, 0.5f);
	reinterpret_cast<UIHP*>(mUIHP)->setEnable(false);

}

