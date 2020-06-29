#pragma once

// a class defining an enemy tank
#include <string>
#include <cassert>

#include "BaseGameEntity.h"
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
	
	void setResetPoint(Vector3 mResetPoint);
	Vector3 getResetPoint()const;
	void setWanderRangeRadiusSq(float mWanderRange);
	float getWanderRangeRadiusSq()const;

	void setMass(float mass);
	float getMass()const;
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

	bool isObstacleForward()const;
	bool isObstacleRight()const;
	bool isObstacleLeft()const;
	bool isCollision()const;

	Vector3 batteryForward()const;
	Vector3 batteryPosition()const;
	void rotateBattery(float x, float y, float z);

private:
	bool m_HPRecovered;
	bool m_Attacked;
	bool m_isObstacleForward;
	bool m_isObstacleRight;
	bool m_isObstacleLeft;
	bool m_isCollision;

	GameObject* mObstacle;
	GameObject* mBattery;
	std::vector<RenderComponent*> mRCs;
};
