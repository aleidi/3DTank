#pragma once
#include "Vector3.h"
#include <vector>

class BoundingCube;
class MBoundingSphere;

class CollisionManager {
public:
	static CollisionManager* sGetInstance();
	static void onInit();
	static void destroy();

	bool collisionCheck_CubeToCube(BoundingCube* cube);
	bool collisionCheck_SphereToCube(const MBoundingSphere* sphere, BoundingCube* cube);
	void rayCheck(const Vector3& origin, const Vector3& direction, BoundingCube* farthestCube, BoundingCube* nearestCube, float& farthestDis, float& nearestDis);
	bool collisionCheck(BoundingCube* cube1, BoundingCube* cube2);
	bool collisionCheck(const BoundingCube* cube, const MBoundingSphere* sphere);
	bool collisionCheck(const Vector3& ori, const Vector3& dir, const BoundingCube* cube, float& dis);

	void deleteBoundingCube(const BoundingCube* cube);
	void deleteBoundingSphere(const MBoundingSphere* sphere);

	void onUpdata(float);

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
	std::vector<MBoundingSphere*>mBoundingSphere;
};