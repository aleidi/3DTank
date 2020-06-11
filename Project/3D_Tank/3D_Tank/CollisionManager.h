#pragma once
#include "Vector3.h"
#include <vector>

class BoundingCube;
class BoundingSphere;

class CollisionManager {
public:
	static CollisionManager* sGetInstance();
	static void onInit();
	static void destroy();

	bool collisionCheck_CubeToCube(const BoundingCube* cube);
	bool collisionCheck_SphereToCube(const BoundingSphere* sphere, BoundingCube* cube);
	bool collisionCheck_RayToCube(const Vector3& ori, const Vector3& dir, const BoundingCube* cube, float& dis);
	void rayCheck(const Vector3& origin, const Vector3& direction, BoundingCube* farthestCube, BoundingCube* nearestCube, float& farthestDis, float& nearestDis);
	bool collisionCheck(const BoundingCube* cube1, const BoundingCube* cube2);
	bool collisionCheck(const BoundingCube* cube, const BoundingSphere* sphere);

	void deleteBoundingCube(const BoundingCube* cube);
	void deleteBoundingSphere(const BoundingSphere* sphere);

	void onUpdata(float);

private:
	static CollisionManager* sInstance;
	CollisionManager();
	~CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager & operator=(const CollisionManager&) = delete;

private:
	friend class BoundingCube;
	friend class BoundingSphere;

	std::vector<BoundingCube*>mBoundingCube;
	std::vector<BoundingCube*>moveableBoundingCube;
	std::vector<BoundingSphere*>mBoundingSphere;
};