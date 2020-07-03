#include "EnemyBoss.h"
#include "FileManager.h"
#include "UIHP.h"

EnemyBoss::EnemyBoss(int id)
{
	mAttribute = { FileManager::AIAttributes[id].m_HP,
			   FileManager::AIAttributes[id].m_HP,
			   FileManager::AIAttributes[id].m_AttackRangeRadiusSq,
			   FileManager::AIAttributes[id].m_PursuitRangeRadiusSq,
			   FileManager::AIAttributes[id].m_WanderRangeRadiusSq,
			   FileManager::AIAttributes[id].m_Mass,
			   FileManager::AIAttributes[id].m_MaxSpeed,
			   FileManager::AIAttributes[id].m_AttackTimeDelay,
			   FileManager::AIAttributes[id].m_Offset,
			   FileManager::AIAttributes[id].m_HitRate,
			   FileManager::AIAttributes[id].m_MaxTurnRate,
			   FileManager::AIAttributes[id].m_WanderRadius,
			   FileManager::AIAttributes[id].m_WanderDistance,
			   FileManager::AIAttributes[id].m_WanderJitter,
			   FileManager::AIAttributes[id].m_ResetPoint };

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

	mBattery = SceneManager::sGetInstance()->createEmptyObject();
	//mBattery->setName("BossBattery");
	//RenderComponent* rc = SceneManager::sGetInstance()->createModel(*mBattery, "Tank\\TankBattery", L"Tank\\TankTex");
	//mBattery->getTransform()->setScale(Vector3(0.1, 0.1, 0.1));
	mBattery->attach(*this);
}

