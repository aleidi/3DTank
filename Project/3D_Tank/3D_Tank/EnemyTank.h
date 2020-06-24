#pragma once

// a class defining an enemy tank
#include <string>
#include <cassert>

#include "BaseGameEntity.h"
#include "EnemyTankOwnedStates.h"
// #include "StateMachine.h"
#include "SceneManager.h"
#include "Transform.h"
const int DyingHP = 20; // below this value the enemy tank is dying
const int FullHP = 100;
const int ReplyInterval = 10;

class EnemyTank : public BaseGameEntity {
public:
	EnemyTank(int ID);
	~EnemyTank();

	//////////////////////////////////////////////////////accessors
	void setHP(int changeHP);
	int getHP()const;
	void setMass(float mass);
	float getMass()const;
	void setMaxSpeed(float maxspeed);
	float getMaxSpeed()const;
	void setVelocity(Vector3 newVelocity);
	Vector3 getVelocity()const;
	float getWanderRadius()const;
	float getWanderDistance()const;
	float getWanderJitter()const;
	void setWanderValue(float radius, float distance, float jitter);
	Vector3 getWanderTarget()const;
	void setWanderTarget(Vector3 wandertarget);

	void move(Vector3 value);
	void setBatteryRotation(Vector3 value);
	bool isDying()const;
	bool isEnemyInRange()const;
	bool isLostEnemy()const;
	bool isObstacleHere()const;
	bool getHPRecovered()const;
	void setHPRecovered(bool isRecovered);
	void setAttacked(bool isAttacked);
	bool getAttacked()const;

private:
	bool m_HPRecovered;
	bool m_Attacked;

	GameObject* mBattery;
	std::vector<RenderComponent*> mRCs;
};
