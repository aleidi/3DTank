#include "EnemyTank.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "ComponentBase.h"
#include "AIMovementComponent.h"

/*
void EnemyTank::update() {
	m_pStateMachine->update();
}
*/
struct Telegram;

EnemyTank::EnemyTank(int ID)
	:m_HPRecovered(false),
	BaseGameEntity(ID)
{
	DirectX::XMVECTOR maxPoint, minPoint;
	mAttribute = {100,1000.0f,2000.0f};
	GameObject* tankBattery = SceneManager::sGetInstance()->createEmptyObject();
	mRCs.push_back(SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBattery", L"Tank\\TankTex", maxPoint, minPoint));
	tankBattery->getTransform()->setScale(0.002f, 0.002f, 0.002f);
	BoundingCube* tankBatteryBoundingCube = new BoundingCube(tankBattery);
	tankBatteryBoundingCube->createBoundingCube(maxPoint, minPoint, 1);
	tankBattery->addComponent(tankBatteryBoundingCube);
	//tankBattery->getTransform()->calcultateTransformMatrix();
	tankBatteryBoundingCube->box.Transform(tankBatteryBoundingCube->box, tankBattery->getTransform()->getLocalToWorldMatrix());
	GameObject* tankBody = SceneManager::sGetInstance()->createEmptyObject();
	mRCs.push_back(SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBody", L"Tank\\TankTex", maxPoint, minPoint));
	tankBody->getTransform()->setScale(0.002f, 0.002f, 0.002f);
	BoundingCube* tankBodyBoundingCube = new BoundingCube(tankBody);
	tankBodyBoundingCube->createBoundingCube(maxPoint, minPoint, 1);
	tankBody->addComponent(tankBodyBoundingCube);
	tankBodyBoundingCube->box.Transform(tankBodyBoundingCube->box, tankBody->getTransform()->getLocalToWorldMatrix());
	this->cube = tankBodyBoundingCube;

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

	mTransform->setScale(0.002f, 0.002f, 0.002f);
	// m_pStateMachine = new StateMachine<EnemyTank>(this);
	// m_pStateMachine->setCurrentState(Rest::getInstance());
	
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

/*
bool EnemyTank::handleMessage(const Telegram& msg) {
	return m_pStateMachine->handleMessage(msg); 
}
*/

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
	if( Vector3::lengthSq( getPosPlayer, mTransform->getPosition() ) <= mAttribute.m_AttackRangeRadiusSq ) {
		// do something here to check if there are any obstacles
		// if no
		return true;
		// else return false;return true; 
	}
	return false;
}

bool EnemyTank::isLostEnemy()const {
	if (Vector3::lengthSq(getPosPlayer, mTransform->getPosition()) > mAttribute.m_PursuitRangeRadiusSq) {
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