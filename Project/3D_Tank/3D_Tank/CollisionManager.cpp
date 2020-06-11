#include "DirectXCollision.h"
#include "CollisionManager.h"
#include "BoundingCube.h"
#include "BoundingSphere.h"

CollisionManager* CollisionManager::sInstance = NULL;

CollisionManager * CollisionManager::sGetInstance()
{
	if (sInstance == NULL)
		sInstance = new CollisionManager();
	return sInstance;
}

void CollisionManager::onInit()
{
	if (sInstance == NULL)
		sInstance = new CollisionManager();
}

void CollisionManager::destroy()
{
	delete sInstance;
	sInstance = NULL;
}

bool CollisionManager::collisionCheck_CubeToCube(const BoundingCube * cube)
{
	if (cube && mBoundingCube.size() > 0) {
		for (std::vector<BoundingCube*>::iterator it = mBoundingCube.begin(); it != mBoundingCube.end(); it++) {
			if (*it == cube) continue;
			if (collisionCheck(cube, *it) == true)
				return true;
		}
		return false;
	}
	else
		return false;
}

bool CollisionManager::collisionCheck_SphereToCube(const BoundingSphere * sphere, BoundingCube* cube)
{
	if (sphere && mBoundingSphere.size() > 0) {
		for (std::vector<BoundingCube*>::iterator it = mBoundingCube.begin(); it != mBoundingCube.end(); it++) {
			if (collisionCheck(*it, sphere)) {
				cube = *it;
				return true;
			}
		}
		return false;
	}
	else
		return false;
}

bool CollisionManager::collisionCheck_RayToCube(const Vector3 & o, const Vector3 & d, const BoundingCube * cube, float & dis)
{
	DirectX::XMFLOAT3 cen(cube->center.x, cube->center.y, cube->center.z);
	DirectX::XMFLOAT3 ext(cube->extents.x, cube->extents.y, cube->extents.z);
	DirectX::BoundingBox box(cen, ext);
	DirectX::XMFLOAT3 ori(o.x, o.y, o.z);
	DirectX::XMFLOAT3 dir(d.x, d.y, d.z);
	DirectX::XMVECTOR origin = DirectX::XMLoadFloat3(&ori);
	DirectX::XMVECTOR direction = DirectX::XMLoadFloat3(&dir);
	return box.Intersects(origin, direction, dis);
}

void CollisionManager::rayCheck(const Vector3 & origin, const Vector3 & direction, BoundingCube * farthestCube, BoundingCube * nearestCube, float & farthestDis, float & nearestDis)
{
	float maxDis = -1.f, minDis = -1.f, dis = 0.f;
	for (std::vector<BoundingCube*>::iterator it = mBoundingCube.begin(); it != mBoundingCube.end(); it++) {
		if (collisionCheck_RayToCube(origin, direction, *it, dis)) {
			if (maxDis == -1.f && minDis == -1.f) {
				maxDis = minDis = dis;
				farthestCube = *it;
				nearestCube = *it;
			}
			else {
				if (dis > maxDis) { maxDis = dis; farthestCube = *it; }
				if (dis < minDis) { minDis = dis; nearestCube = *it; }
			}
		}
	}

}

bool CollisionManager::collisionCheck(const BoundingCube * cube1, const BoundingCube * cube2)
{
	DirectX::XMFLOAT3 cen(cube1->center.x, cube1->center.y, cube1->center.z);
	DirectX::XMFLOAT3 ext(cube1->extents.x, cube1->extents.y, cube1->extents.z);
	DirectX::BoundingBox box1(cen, ext);
	cen.x = cube2->center.x; cen.y = cube2->center.y; cen.z = cube2->center.z;
	ext.x = cube2->extents.x; ext.y = cube2->extents.y; ext.z = cube2->extents.z;
	DirectX::BoundingBox box2(cen, ext);
	return box1.Intersects(box2);
}

bool CollisionManager::collisionCheck(const BoundingCube * cube, const BoundingSphere * sphere)
{
	DirectX::XMFLOAT3 cen(cube->center.x, cube->center.y, cube->center.z);
	DirectX::XMFLOAT3 ext(cube->extents.x, cube->extents.y, cube->extents.z);
	DirectX::BoundingBox box(cen, ext);
	cen.x = sphere->center.x; cen.y = sphere->center.y; cen.z = sphere->center.z;
	DirectX::BoundingSphere DXSphere(cen, sphere->radius);
	return box.Intersects(DXSphere);
}

void CollisionManager::deleteBoundingCube(const BoundingCube* cube)
{
	if (cube && mBoundingCube.size() > 0) {
		for (std::vector<BoundingCube*>::iterator it = mBoundingCube.begin(); it != mBoundingCube.end(); it++) {
			if (*it == cube) {
				delete *it;
				*it = NULL;
				mBoundingCube.erase(it);
			}
		}
	}
}

void CollisionManager::deleteBoundingSphere(const BoundingSphere * sphere)
{
	if (sphere && mBoundingSphere.size() > 0) {
		for (std::vector<BoundingSphere*>::iterator it = mBoundingSphere.begin(); it != mBoundingSphere.end(); it++) {
			if (*it == sphere) {
				delete *it;
				*it = NULL;
				mBoundingSphere.erase(it);
			}
		}
	}
}

void CollisionManager::onUpdata(float deltaTime)
{
	if (moveableBoundingCube.size() > 0) {
		for (std::vector<BoundingCube*>::iterator it = moveableBoundingCube.begin(); it != moveableBoundingCube.end(); it++) {
			(*it)->onFixedUpdate(deltaTime);
		}
	}
}

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
	for (std::vector<BoundingCube*>::iterator it = mBoundingCube.begin(); it != mBoundingCube.end(); it++) {
		if (*it) {
			delete *it;
			*it = NULL;
		}
	}
	for (std::vector<BoundingSphere*>::iterator it = mBoundingSphere.begin(); it != mBoundingSphere.end(); it++) {
		if (*it) {
			delete *it;
			*it = NULL;
		}
	}
}
