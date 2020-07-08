#include "EnemyBoss.h"
#include "FileManager.h"
#include "UIHP.h"
#include "UIImage.h"
#include "UIImage3D.h"
#include "UIText.h"
#include "GameCommon.h"
#include "BoundingCube.h"
#include "MagicBall.h"
#include "GameInstance.h"

EnemyBoss::EnemyBoss(int id)
	:mCanSuperAttack(false),mCanFloat(false),mSAParticles(),mSAIndex(0),mTimerSA(0.0f),mIntervalSA(1.0f)
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

	mTransform->setScale(0.25f, 0.25f, 0.25f);
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

	initParticles();
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

void EnemyBoss::onLateUpdate(const float& deltaTime)
{
	mImage->setFillAmount((float)mAttribute.m_HP / (float)mAttribute.FullHP);
}

void EnemyBoss::onUpdate(const float& deltaTime)
{
	if (mCanFloat)
	{
		doFloat(deltaTime);
	}

	if (mCanSuperAttack)
	{
		mTimerSA += deltaTime;
		if (mTimerSA > mIntervalSA)
		{
			doSuperAttack();
			mTimerSA = 0.0f;
		}
	}

}

void EnemyBoss::onCollisionEnter()
{
}

void EnemyBoss::enableSuperAttack(bool value)
{
	mCanSuperAttack = value;
}

void EnemyBoss::enableFloat(bool value)
{
	mCanFloat = value;
}

void EnemyBoss::initParticles()
{
	mPSAttack = SceneManager::sGetInstance()->createParticleSystem(L"VFX/T_Fire_Shock_01");
	mPSAttack->setTile(5.0f, 5.0f);
	mPSAttack->setEmitter(ParticleSystem::Emitter::NoEmit);
	mPSAttack->setEmitRate(1);
	mPSAttack->setLifeTime(0.3f);
	mPSAttack->setAnimationInterval(0.3f / 25.0f);
	mPSAttack->setStartScale(0.2f, 0.2f, 0.2f);
	mPSAttack->setDuration(0.3f);
	mPSAttack->setStartScale(1.0f, 1.0f, 1.0f);
	Material mat;
	mat.Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mPSAttack->setMaterial(mat);

	mPSHited = SceneManager::sGetInstance()->createParticleSystem(L"VFX/T_Fire_Shock_01");
	mPSHited->setTile(5.0f, 5.0f);
	mPSHited->setEmitter(ParticleSystem::Emitter::NoEmit);
	mPSHited->setEmitRate(1);
	mPSHited->setLifeTime(0.3f);
	mPSHited->setAnimationInterval(0.2f / 25.0f);
	mPSHited->setStartScale(0.5f, 0.5f, 0.5f);
	mPSHited->setDuration(0.3f);
	mPSAttack->setStartScale(1.0f, 1.0f, 1.0f);

	mPSDeath = SceneManager::sGetInstance()->createParticleSystem(L"VFX/xulie_fire052_5x5");
	mPSDeath->setTile(5.0f, 5.0f);
	mPSDeath->setEmitter(ParticleSystem::Emitter::NoEmit);
	mPSDeath->setEmitRate(1);
	mPSDeath->setLifeTime(1.0f);
	mPSDeath->setAnimationInterval(1.0f / 25.0f);
	mPSDeath->setStartScale(0.3f, 0.3f, 0.3f);
	mPSDeath->setDuration(10.0f);

	mPSSuperAttack = SceneManager::sGetInstance()->createParticleSystem(L"VFX/fazhen_00003", 10);
	mPSSuperAttack->setEmitter(ParticleSystem::Emitter::Box);
	mPSSuperAttack->enableLoop(true);
	mPSSuperAttack->setEmitRate(5);
	mPSSuperAttack->setPosition(0.0f, 0.0f, 3.0f);
	mPSSuperAttack->setLifeTime(50.0f);
	mPSSuperAttack->setStartScale(1.5f, 1.5f, 1.5f);
	mPSSuperAttack->setVelocity(0.0f, 0.0f, 0.0f);
	mPSSuperAttack->setRange(0.5f, 1.5f, 0.5f);
}

void EnemyBoss::playSuperAttackParticle()
{
	Vector3 pos = mTransform->getPosition() + Vector3::up*6.0f;
	mPSSuperAttack->setPosition(pos.x, pos.y, pos.z);
	mPSSuperAttack->play();
}

void EnemyBoss::doFloat(const float & deltaTime)
{
	mOffset += deltaTime;
	if (mOffset > 2 * Pi)
	{
		mOffset = 0.0f;
	}
	mTransform->translate(Vector3(0.0f, sinf(mOffset)*deltaTime, 0.0f));
}

void EnemyBoss::doSuperAttack()
{
	auto mb = new MagicBall();
	mb->getTransform()->setPosition(
		Vector3(mSAParticles[mSAIndex].Position.x, mSAParticles[mSAIndex].Position.y,mSAParticles[mSAIndex].Position.z));
	mb->setTarget(GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition());
	mb->setTaragetPawn(*GameInstance::sGetInstance()->getPlayer());
	mb->setTile((float)rand() / (float)RAND_MAX * 3.0f, (float)rand() / (float)RAND_MAX * 2.0f);
	mb->enableTile(true);
	//mb->setSpeed(3.0f);
	mb->enableChase(true);
	++mSAIndex;
	if (mSAIndex > mSAParticles.size() - 1)
	{
		mSAIndex = 0;
	}
}

void EnemyBoss::preDoSuperAttack()
{
	mSAParticles = mPSSuperAttack->getParticles();
	mSAIndex = 0;
}
