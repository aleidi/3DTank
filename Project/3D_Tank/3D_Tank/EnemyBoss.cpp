#include "EnemyBoss.h"
#include "FileManager.h"
#include "UIHP.h"
#include "UIImage.h"

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
	mUIHP->setEnable(false);

	mFrame = SceneManager::sGetInstance()->createUIImage(L"UI/BossHP_Frame");
	mFrame->setPosition(WINDOW_WIDTH * (0.5f-0.315f), WINDOW_HEIGHT*0.770f);
	mFrame->setSize(WINDOW_WIDTH * 0.63f, WINDOW_HEIGHT * 0.06f);

	mImage = SceneManager::sGetInstance()->createUIImage(L"");
	mImage->setPosition(WINDOW_WIDTH*0.2f, WINDOW_HEIGHT*0.775f);
	mImage->setSize(WINDOW_WIDTH * 0.6f, WINDOW_HEIGHT * 0.05f);
	Material mat;
	mat.Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	mImage->setMaterial(mat);

	mBattery = SceneManager::sGetInstance()->createEmptyObject();
	mBattery->setName("BossBattery");
	RenderComponent* rc = SceneManager::sGetInstance()->createModel(*mBattery, "Tank\\TankBattery", L"Tank\\TankTex");
	mBattery->getTransform()->setScale(Vector3(0.1, 0.1, 0.1));
	mBattery->attach(*this);
}

EnemyBoss::~EnemyBoss()
{

}

void EnemyBoss::showHP(bool value)
{
	mFrame->setEnable(value);
	mImage->setEnable(value);
}

