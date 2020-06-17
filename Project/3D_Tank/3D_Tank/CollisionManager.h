#pragma once
#include "Vector3.h"
#include <vector>

class GameObject;
class BoundingCube;
class MBoundingSphere;

class CollisionManager {
public:
	static CollisionManager* sGetInstance();
	static void onInit();
	static void destroy();

	bool collisionCheck_CubeToCube(const BoundingCube* cube, GameObject* obj);
	bool collisionCheck_SphereToCube(const MBoundingSphere* sphere, GameObject* obj);
	bool rayCheck(const Vector3& origin, const Vector3& direction, BoundingCube* farthestCube, BoundingCube* nearestCube, float& farthestDis, float& nearestDis);
	bool rayCheckWithObstacle(const Vector3& origin, const Vector3& direction, const float& farthestDis, GameObject* gameobject, float& dis);
	bool collisionCheck(const BoundingCube* cube1, const BoundingCube* cube2);
	bool collisionCheck(const BoundingCube* cube, const MBoundingSphere* sphere);
	bool collisionCheck(const Vector3& ori, const Vector3& dir, const BoundingCube* cube, float& dis);

	void deleteBoundingCube(const BoundingCube* cube);
	void deleteBoundingSphere(const MBoundingSphere* sphere);

	void onUpdata(float);

protected:
	//virtual void onCollisionEnter();
	//virtual void onCollisionStay();
	//virtual void onCollisionExit();

	//virtual void onTriggerEnter();
	//virtual void onTriggerStay();
	//virtual void onTriggerExit();

private:
	static CollisionManager* sInstance;
	CollisionManager();
	~CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager & operator=(const CollisionManager&) = delete;

private:
	friend class BoundingCube;
	friend class MBoundingSphere;

	std::vector<BoundingCube*>mBoundingCube;
	std::vector<BoundingCube*>moveableBoundingCube;
	std::vector<BoundingCube*>unmoveableBoundingCube;
	std::vector<MBoundingSphere*>mBoundingSphere;
};