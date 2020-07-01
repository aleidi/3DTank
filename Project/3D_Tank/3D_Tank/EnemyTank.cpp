#pragma once
#include <DirectXMath.h>
#include "EnemyTank.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "ComponentBase.h"
#include "AIMovementComponent.h"
#include "GameInstance.h"
#include "CollisionManager.h"
#include "Shell.h"
#include "FileManager.h"
#include "Math.h"
#include "DamageDisplay.h"
#include "AIController.h"

struct Telegram;
#define getTargetPos getAICtrl()->getTarget()->getTransform()->getPosition()

EnemyTank::EnemyTank(int ID, float scale)
	:m_HPRecovered(false),
	m_Attacked(false),
	BaseGameEntity(ID)
{
	DirectX::XMVECTOR maxPoint, minPoint;
	mAttribute = { FileManager::AIAttributes[ID].m_HP,
				   FileManager::AIAttributes[ID].m_HP,
				   FileManager::AIAttributes[ID].m_AttackRangeRadiusSq,
				   FileManager::AIAttributes[ID].m_PursuitRangeRadiusSq,
				   FileManager::AIAttributes[ID].m_WanderRangeRadiusSq,
				   FileManager::AIAttributes[ID].m_Mass,
				   FileManager::AIAttributes[ID].m_MaxSpeed,
				   FileManager::AIAttributes[ID].m_AttackTimeDelay,
				   FileManager::AIAttributes[ID].m_Offset,
				   FileManager::AIAttributes[ID].m_HitRate,
				   FileManager::AIAttributes[ID].m_MaxTurnRate,
				   FileManager::AIAttributes[ID].m_WanderRadius,
				   FileManager::AIAttributes[ID].m_WanderDistance,
				   FileManager::AIAttributes[ID].m_WanderJitter,
				   FileManager::AIAttributes[ID].m_ResetPoint };

	FullHP = mAttribute.FullHP;
	DyingHP = FullHP * 0.2; // below this value the enemy tank is dying
	mTag = ObjectTag::Enemy;

	mRCs.push_back(SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBody", L"Tank\\TankTex", maxPoint, minPoint));
	DirectX::XMFLOAT3 maxP0(108.550003f, 97.2149963f, 177.554993f);
	DirectX::XMFLOAT3 minP0(-86.8899994f, 3.51500010f, -191.240005f);
	maxPoint = DirectX::XMLoadFloat3(&maxP0); minPoint = DirectX::XMLoadFloat3(&minP0);
	BoundingCube* bodyBoundingCube = new BoundingCube(this);
	bodyBoundingCube->createBoundingCube(maxPoint, minPoint, 1);
	this->addComponent(bodyBoundingCube);
	//mRCs.push_back(SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBattery", L"Tank\\TankTex", maxPoint, minPoint));
	//mRCs.push_back(SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBody", L"Tank\\TankTex"));
	mRCs.push_back(SceneManager::sGetInstance()->createModel(*this, "Tank\\TankTrack_L", L"Tank\\TankTrack"));
	mRCs.push_back(SceneManager::sGetInstance()->createModel(*this, "Tank\\TankTrack_R", L"Tank\\TankTrack"));

	Material mat;
	mat.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mat.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mat.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);
	mat.Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	for (std::vector<RenderComponent*>::iterator it = mRCs.begin(); it != mRCs.end(); ++it)
	{
		if (*it != nullptr)
		{
			(*it)->setMaterial(mat);
		}
	}
	mBattery = SceneManager::sGetInstance()->createEmptyObject();
	mBattery->setName("Battery");
	RenderComponent* rc = SceneManager::sGetInstance()->createModel(*mBattery, "Tank\\TankBattery", L"Tank\\TankTex", maxPoint, minPoint);
	//DirectX::XMFLOAT3 maxP(93.4250031f, 210.244995f, 299.684998f);
	//DirectX::XMFLOAT3 minP(-71.5699997f, 70.3600006f, -106.195000f);
	//maxPoint = DirectX::XMLoadFloat3(&maxP); minPoint = DirectX::XMLoadFloat3(&minP);
	//BoundingCube* tankBatteryBoundingCube = new BoundingCube(mBattery);
	//mBattery->cube = tankBatteryBoundingCube;
	//tankBatteryBoundingCube->createBoundingCube(maxPoint, minPoint, 1);
	//mBattery->addComponent(tankBatteryBoundingCube);
	rc->setMaterial(mat);
	//mBattery->addComponent(rc);
	mBattery->attach(*this);

	mTransform->setScale(scale, scale, scale);
	mTransform->calcultateTransformMatrix();
	// m_pStateMachine = new StateMachine<EnemyTank>(this);
	// m_pStateMachine->setCurrentState(Rest::getInstance());
	DirectX::BoundingOrientedBox out;
	bodyBoundingCube->box.Transform(out, mTransform->getLocalToWorldMatrix());
	bodyBoundingCube->box = out;
	this->cube = bodyBoundingCube;
	/*DirectX::BoundingOrientedBox out1;
	tankBatteryBoundingCube->box.Transform(out1, mTransform->getLocalToWorldMatrix());
	tankBatteryBoundingCube->box = out1;
	mBattery->cube = tankBatteryBoundingCube;*/

	float theta = Math::RandFloat() * 2 * Pi;
	mAttribute.m_WanderTarget = Vector3(mAttribute.m_WanderRadius * cos(theta), 0, mAttribute.m_WanderRadius * sin(theta));

	mMovementComp = new AIMovementComponent(this);
	addComponent(mMovementComp);
	moveDirection = FORWARD;

}

EnemyTank::EnemyTank(int ID)
	:EnemyTank(ID, 0.002f)
{	
}	

EnemyTank::~EnemyTank()
{
	mBattery->destroy();
	mRCs.clear();
	std::vector<RenderComponent*>().swap(mRCs);
}


void EnemyTank::setHP(int changeHP) {
	mAttribute.m_HP += changeHP;
}

int EnemyTank::getHP()const {
	return mAttribute.m_HP;
}

void EnemyTank::setResetPoint(Vector3 mResetPoint) {
	mAttribute.m_ResetPoint = mResetPoint;
}

Vector3 EnemyTank::getResetPoint()const {
	return mAttribute.m_ResetPoint;
}

void EnemyTank::setWanderRangeRadiusSq(float mWanderRangeRadiusSq) {
	mAttribute.m_WanderRangeRadiusSq = mWanderRangeRadiusSq;
}

float EnemyTank::getWanderRangeRadiusSq()const {
	return mAttribute.m_WanderRangeRadiusSq;
}

void EnemyTank::setMass(float mass) {
	mAttribute.m_Mass = mass;
}

float EnemyTank::getMass()const {
	return mAttribute.m_Mass;
}

float EnemyTank::attackTimeDelay ()const {
	return mAttribute.m_AttackTimeDelay;
}

float EnemyTank::offset()const {
	return mAttribute.m_Offset;
}

int EnemyTank::hitRate()const {
	return mAttribute.m_HitRate;
}

float EnemyTank::maxTurnRate()const {
	return mAttribute.m_MaxTurnRate;
}

void EnemyTank::move(Vector3 value)
{
	mMovementComp->addForce(value);
}

void EnemyTank::rotateBattery(float x, float y, float z)
{
	mBattery->getTransform()->rotate(x, y, z);
}

void EnemyTank::onTriggerEnter(const GameObject * obj)
{

}

void EnemyTank::onTriggerExit()
{

}

void EnemyTank::onCollisionEnter()
{
	float damage = (float)rand() / (float)RAND_MAX * 30.0f + 1.0f;
	this->setHP(damage * -1.0f);
	Vector3 pos = mTransform->getPosition();
	pos.x += (float)rand() / (float)RAND_MAX - 0.5f;
	pos.y += (float)rand() / (float)RAND_MAX * 0.6f - 0.2f;
	auto dd = new DamageDisplay(damage, pos);
	float size = damage * 0.1f;
	Math::Clamp(3.0f, 1.0f, size);
	dd->setSizeScale(size, size);
}

void EnemyTank::onCollisionExit()
{
}

void EnemyTank::setAICtrl(AIController * aiController)
{
	mAICtrl = aiController;
}

AIController* EnemyTank::getAICtrl()const {
	return mAICtrl;
}

Vector3 EnemyTank::batteryForward() const {
	return mBattery->getTransform()->Forward;
}

Vector3 EnemyTank::batteryPosition() const {
	return mBattery->getTransform()->getPosition();
}

bool EnemyTank::isDying()const {
	if (mAttribute.m_HP <= DyingHP) {
		return true;
	}

	return false;
}

bool EnemyTank::getHPRecovered()const {
	return this->m_HPRecovered;
}

void EnemyTank::setHPRecovered( bool isRecovered ) {
	this->m_HPRecovered = isRecovered;
}

bool EnemyTank::isEnemyInRange()const {
	if( Vector3::lengthSq( getTargetPos, mTransform->getPosition() ) <= mAttribute.m_AttackRangeRadiusSq ) {
		//check if there are any obstacles
		bool isObstacle = CollisionManager::sGetInstance()->rayCheckWithObstacle(mTransform->getPosition(),
															   (getTargetPos - mTransform->getPosition()).normalize(),
															   sqrt(Vector3::lengthSq(getTargetPos, mTransform->getPosition())));
		if( !isObstacle ) 
			return true;
		else return false;
	}
	return false;
}

bool EnemyTank::isLostEnemy()const {
	if (Vector3::lengthSq(getTargetPos, mTransform->getPosition()) > mAttribute.m_PursuitRangeRadiusSq) {
		return true;
	}
	return false;
}

void EnemyTank::setAttacked(bool isAttacked) {
	this->m_Attacked = isAttacked;
}

bool EnemyTank::getAttacked()const {
	return this->m_Attacked;
}

GameObject * EnemyTank::getBattery()
{
	return mBattery;
}

bool EnemyTank::isObstacleHere() {
	Vector3 feelersForward = this->getTransform()->Forward;
	Vector3 feelersRight = (this->getTransform()->Forward + this->getTransform()->Right).normalize();
	Vector3 feelersLeft = (this->getTransform()->Forward + this->getTransform()->Right * -1).normalize();

	m_isObstacleForward = false;
	m_isObstacleLeft = false;
	m_isObstacleRight = false;
	m_isCollision = false;

	if (CollisionManager::sGetInstance()->rayCheckWithObstacle(this->getTransform()->getPosition(), feelersRight, 2.0f)) {
		m_isObstacleRight = true;
		return true;
	}

	if (CollisionManager::sGetInstance()->rayCheckWithObstacle(this->getTransform()->getPosition(), feelersLeft, 2.0f)) {
		m_isObstacleLeft = true;
		return true;
	}

	if (CollisionManager::sGetInstance()->rayCheckWithObstacle(this->getTransform()->getPosition(), feelersForward, 2.0f)) {
		m_isObstacleForward = true;
		return true;
	}

	if (CollisionManager::sGetInstance()->collisionCheck_CubeToCube(this->cube, &mObstacle)) {
		m_isCollision = true;
		return true;
	}

	return false;
}

bool EnemyTank::isObstacleForward()const {
	return m_isObstacleForward;
}

bool EnemyTank::isObstacleRight()const {
	return m_isObstacleRight;
}

bool EnemyTank::isObstacleLeft()const {
	return m_isObstacleLeft;
}

bool EnemyTank::isCollision()const {
	return m_isCollision;
}

float EnemyTank::getWanderRadius()const {
	return mAttribute.m_WanderRadius;
}

float EnemyTank::getWanderDistance()const {
	return mAttribute.m_WanderDistance;
}

float EnemyTank::getWanderJitter()const {
	return mAttribute.m_WanderJitter;
}

Vector3 EnemyTank::getWanderTarget()const{
	return mAttribute.m_WanderTarget;
}

void EnemyTank::setWanderTarget(Vector3 wandertarget) {
	mAttribute.m_WanderTarget = wandertarget;
}

void EnemyTank::setWanderValue(float radius, float distance, float jitter) {
	mAttribute.m_WanderRadius = radius;
	mAttribute.m_WanderDistance = distance;
	mAttribute.m_WanderJitter = jitter;
}

