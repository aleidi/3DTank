#include "EnemyBoss.h"
#include "FileManager.h"
#include "UIHP.h"
#include "UIImage.h"
#include "UIImage3D.h"
#include "UIText.h"
#include "GameCommon.h"
#include "BoundingCube.h"
#include "SoundManager.h"

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

	//create normal model
	mNormalModel = SceneManager::sGetInstance()->createEmptyObject();
	SceneManager::sGetInstance()->createModel(*mNormalModel, "Boss/RedBaronN/m0_Arm_Base_Color", L"Boss/RedBaronN/Arm_Base_Color");
	SceneManager::sGetInstance()->createModel(*mNormalModel, "Boss/RedBaronN/m1_Body_Base_Color", L"Boss/RedBaronN/Body_Base_Color");
	SceneManager::sGetInstance()->createModel(*mNormalModel, "Boss/RedBaronN/m2_Chest_Base_Color", L"Boss/RedBaronN/Chest_Base_Color");
	SceneManager::sGetInstance()->createModel(*mNormalModel, "Boss/RedBaronN/m3_Fire", L"Boss/RedBaronN/Fire");
	SceneManager::sGetInstance()->createModel(*mNormalModel, "Boss/RedBaronN/m4_HeadHigh_Base_Color", L"Boss/RedBaronN/HeadHigh_Base_Color");
	SceneManager::sGetInstance()->createModel(*mNormalModel, "Boss/RedBaronN/m5_Leg_Base_Color", L"Boss/RedBaronN/Leg_Base_Color");
	SceneManager::sGetInstance()->createModel(*mNormalModel, "Boss/RedBaronN/m6_Sholder_Base_Color", L"Boss/RedBaronN/Sholder_Base_Color");
	SceneManager::sGetInstance()->createModel(*mNormalModel, "Boss/RedBaronN/m7_SubArm_Base_Color", L"Boss/RedBaronN/SubArm_Base_Color");
	mNormalModel->attach(*this);
	//mNormalModel->enableDraw(false);

	//create super model
	mSuperModel = SceneManager::sGetInstance()->createEmptyObject();
	SceneManager::sGetInstance()->createModel(*mSuperModel, "Boss/RedBaronS/m0_Arm_Base_Color", L"Boss/RedBaronS/Arm_Base_Color");
	SceneManager::sGetInstance()->createModel(*mSuperModel, "Boss/RedBaronS/m1_Body_Base_Color", L"Boss/RedBaronS/Body_Base_Color");
	SceneManager::sGetInstance()->createModel(*mSuperModel, "Boss/RedBaronS/m2_Chest_Base_Color", L"Boss/RedBaronS/Chest_Base_Color");
	SceneManager::sGetInstance()->createModel(*mSuperModel, "Boss/RedBaronS/m3_Fire", L"Boss/RedBaronS/Fire");
	SceneManager::sGetInstance()->createModel(*mSuperModel, "Boss/RedBaronS/m4_HeadHigh_Base_Color", L"Boss/RedBaronS/HeadHigh_Base_Color");
	SceneManager::sGetInstance()->createModel(*mSuperModel, "Boss/RedBaronS/m5_Leg_Base_Color", L"Boss/RedBaronS/Leg_Base_Color");
	SceneManager::sGetInstance()->createModel(*mSuperModel, "Boss/RedBaronS/m6_Sholder_Base_Color", L"Boss/RedBaronS/Sholder_Base_Color");
	SceneManager::sGetInstance()->createModel(*mSuperModel, "Boss/RedBaronS/m7_SubArm_Base_Color", L"Boss/RedBaronS/SubArm_Base_Color");
	mSuperModel->attach(*this);
	mSuperModel->enableDraw(false);

	mTransform->setScale(0.5f, 0.5f, 0.5f);
	mUIHP->setEnable(false);

	mFrame = SceneManager::sGetInstance()->createUIImage(L"VFX/BossHP_Frame");
	mFrame->setPosition(WINDOW_WIDTH * (0.5f-0.3375f), WINDOW_HEIGHT*(0.79f-0.0235f));
	mFrame->setSize(WINDOW_WIDTH * 0.675f, WINDOW_HEIGHT * 0.047f);

	mImage = SceneManager::sGetInstance()->createUIImage(L"");
	mImage->setPosition(WINDOW_WIDTH*0.2f, WINDOW_HEIGHT*0.775f);
	mImage->setSize(WINDOW_WIDTH * 0.6f, WINDOW_HEIGHT * 0.03f);
	Material mat;
	mat.Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	mImage->setMaterial(mat);
	mImage->setFillType(FillType::HR);

	mName = SceneManager::sGetInstance()->createUIText(L"???");
	mName->setPosition(WINDOW_WIDTH*0.5f, WINDOW_HEIGHT*0.82f);
	mName->setSize(WINDOW_WIDTH*0.01f, WINDOW_HEIGHT*0.02f);
	showUI(false);

	mBattery = SceneManager::sGetInstance()->createEmptyObject();
	//mBattery->setName("BossBattery");
	//RenderComponent* rc = SceneManager::sGetInstance()->createModel(*mBattery, "Tank\\TankBattery", L"Tank\\TankTex");
	//mBattery->getTransform()->setScale(Vector3(0.1, 0.1, 0.1));
	mBattery->attach(*this);

	cube = new BoundingCube(this);
	this->addComponent(cube);
	cube->createBoundingCube(mTransform->getPosition() + mTransform->Up * 6.f,Vector3(4.5f, 5.5f, 4.5f),1);
}

EnemyBoss::~EnemyBoss()
{
	mNormalModel->destroy();
	mSuperModel->destroy();
	SceneManager::sGetInstance()->removreUIFromPool(mFrame);
	SceneManager::sGetInstance()->removreUIFromPool(mImage);
	SceneManager::sGetInstance()->removreUIFromPool(mName);
}

void EnemyBoss::showUI(bool value)
{
	mFrame->setEnable(value);
	mImage->setEnable(value);
	mName->setEnable(value);
}

void EnemyBoss::ChangeMode(Mode mode)
{
	switch (mode)
	{
	case EnemyBoss::Normal:
		mNormalModel->enableDraw(true);
		mSuperModel->enableDraw(false);
		break;
	case EnemyBoss::Super:
		mNormalModel->enableDraw(false);
		mSuperModel->enableDraw(true);
		break;
	}
}

void EnemyBoss::onLateUpdate(float deltaTime)
{
	mImage->setFillAmount((float)mAttribute.m_HP / (float)mAttribute.FullHP);
}

void EnemyBoss::onUpdate(float deltaTime)
{
	mOffset += deltaTime;
	if (mOffset > 2 * Pi)
	{
		mOffset = 0.0f;
	}
	mTransform->translate(Vector3(0.0f, sinf(mOffset)*deltaTime, 0.0f));
}

void EnemyBoss::onCollisionEnter()
{
	SoundManager::sGetInstance()->playBGM();
}
