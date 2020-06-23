#pragma once
#include "EnemyTank.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "ComponentBase.h"
#include "AIMovementComponent.h"
#include "GameInstance.h"
#include "CollisionManager.h"
/*
void EnemyTank::update() {
	m_pStateMachine->update();
}
*/
struct Telegram;
#define getPlayerPos GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition()
EnemyTank::EnemyTank(int ID)
	:m_HPRecovered(false),
	m_Attacked(false),
	BaseGameEntity(ID)
{

	mAttribute = {100,1000.0f,2000.0f,50.0f,1.0f,10.0f,20.0f,800.0f};
	mRCs.push_back(SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBattery", L"Tank\\TankTex"));
	mRCs.push_back(SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBody", L"Tank\\TankTex"));
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

	mTransform->setScale(0.002f, 0.002f, 0.002f);
	// m_pStateMachine = new StateMachine<EnemyTank>(this);
	// m_pStateMachine->setCurrentState(Rest::getInstance());

	float theta = Math::RandFloat() * 2 * Pi;
	mAttribute.m_WanderTarget = Vector3(mAttribute.m_WanderRadius * cos(theta), 0, mAttribute.m_WanderRadius * sin(theta));

	mMovementComp = new AIMovementComponent(this);
	addComponent(mMovementComp);
	
}	

EnemyTank::~EnemyTank()
{
	mRCs.clear();
	std::vector<RenderComponent*>().swap(mRCs);
}


void EnemyTank::setHP(int changeHP) {
	mAttribute.m_HP += changeHP;
}

int EnemyTank::getHP()const {
	return mAttribute.m_HP;
}

void EnemyTank::setMass(float mass) {
	mAttribute.m_Mass = mass;
}

float EnemyTank::getMass()const {
	return mAttribute.m_Mass;
}

void EnemyTank::setMaxSpeed(float maxspeed) {
	mAttribute.m_MaxSpeed = maxspeed;
}

float EnemyTank::getMaxSpeed()const {
	return mAttribute.m_MaxSpeed;
}

void EnemyTank::setVelocity(Vector3 newVelocity) {
	m_Velocity = newVelocity;
}

Vector3 EnemyTank::getVelocity()const {
	return m_Velocity;
}

void EnemyTank::move(Vector3 value)
{
	mMovementComp->addForce(value);
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
	if( Vector3::lengthSq( getPlayerPos, mTransform->getPosition() ) <= mAttribute.m_AttackRangeRadiusSq ) {
		//check if there are any obstacles
		float distance = 0.0f;
		bool isObstacle = CollisionManager::sGetInstance()->rayCheckWithObstacle(mTransform->getPosition(),
															   (getPlayerPos - mTransform->getPosition()).normalize(),
															   sqrt(Vector3::lengthSq(getPlayerPos, mTransform->getPosition())),
															   nullptr, distance);
		if( !isObstacle ) return true;
		else return false;
		// else return false;return true; 
	}
	return false;
}

bool EnemyTank::isLostEnemy()const {
	if (Vector3::lengthSq(getPlayerPos, mTransform->getPosition()) > mAttribute.m_PursuitRangeRadiusSq) {
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

bool EnemyTank::isObstacleHere()const {
	return false;
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