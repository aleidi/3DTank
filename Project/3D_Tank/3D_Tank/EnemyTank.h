#pragma once

// a class defining an enemy tank
#include <string>
#include <cassert>

#include "BaseGameEntity.h"
#include "SceneManager.h"
#include "Transform.h"
class Shell;
class AIController;
class ParticleSystem;

class EnemyTank : public BaseGameEntity{
public:
	EnemyTank(int ID, float scale);
	EnemyTank(int ID);
	EnemyTank();
	~EnemyTank();

	//////////////////////////////////////////////////////accessors
	int FullHP;
	int DyingHP; // below this value the enemy tank is dying
	int ReplyInterval = 3;

	void setHP(int changeHP);
	int getHP()const;
	
	void setResetPoint(Vector3 mResetPoint);
	Vector3 getResetPoint()const;
	void setWanderRangeRadiusSq(float mWanderRange);
	float getWanderRangeRadiusSq()const;

	void setMass(float mass);
	float getMass()const;
	float attackTimeDelay()const;
	float offset()const;
	int hitRate()const;
	float maxTurnRate()const;
	float getWanderRadius()const;
	float getWanderDistance()const;
	float getWanderJitter()const;
	void setWanderValue(float radius, float distance, float jitter);
	Vector3 getWanderTarget()const;
	void setWanderTarget(Vector3 wandertarget);

	void move(Vector3 value);
	bool isDying()const;
	bool isEnemyInRange()const;
	bool isLostEnemy()const;
	bool isObstacleHere();
	bool getHPRecovered()const;
	void setHPRecovered(bool isRecovered);
	void setAttacked(bool isAttacked);
	bool getAttacked()const;
	GameObject* getBattery();

	bool isObstacleForward()const;
	bool isObstacleRight()const;
	bool isObstacleLeft()const;

	bool isPatrol()const;
	Vector3 patrolEnd()const;
	Vector3 patrolStart()const;

	bool isMissile()const;

	Vector3 batteryForward()const;
	Vector3 batteryPosition()const;
	void rotateBattery(float x, float y, float z);

	void onTriggerEnter(const GameObject* obj) override;
	void onTriggerExit() override;
	void onCollisionEnter() override;
	void onCollisionExit() override;

	void playAttackParticle();
	void playDeathParticle();

	float aiCount = 0.0f;

	void hited(int value);

	void setAICtrl(AIController* aiController);
	AIController* getAICtrl()const;

protected:
	virtual void initParticles();
	void playHitedParticle();

protected:
	bool m_HPRecovered;
	bool m_Attacked;
	bool m_isObstacleForward;
	bool m_isObstacleRight;
	bool m_isObstacleLeft;
	//bool m_isCollision;

	GameObject* mObstacle;
	GameObject* mBattery;
	std::vector<RenderComponent*> mRCs;

	ParticleSystem* mPSAttack;
	ParticleSystem* mPSHited;
	ParticleSystem* mPSDeath;
	
	AIController* mAICtrl;
};
