#include "DirectXCollision.h"
#include "CollisionManager.h"
#include "BoundingCube.h"
#include "BoundingSphere.h"
#include "GameObject.h"

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

bool CollisionManager::collisionCheck_CubeToCube(const BoundingCube * cube, GameObject* obj)
{
	if (cube && mBoundingCube.size() > 0) {
		for (std::vector<BoundingCube*>::iterator it = mBoundingCube.begin(); it != mBoundingCube.end(); it++) {
			if (*it == cube) continue;
			if (collisionCheck(cube, *it) == true) {
				
				return true;
			}
		}
		return false;
	}
	else
		return false;
}

bool CollisionManager::collisionCheck_SphereToCube(const MBoundingSphere * sphere, GameObject* obj)
{
	if (sphere && mBoundingSphere.size() > 0) {
		for (std::vector<BoundingCube*>::iterator it = mBoundingCube.begin(); it != mBoundingCube.end(); it++) {
			if (collisionCheck(*it, sphere)) {
				obj = (*it)->getObject();
				return true;
			}
		}
		return false;
	}
	else
		return false;
}

bool CollisionManager::collisionCheck(const Vector3 & o, const Vector3 & d, const BoundingCube * cube, float & dis)
{
	DirectX::XMFLOAT3 ori(o.x, o.y, o.z);
	DirectX::XMFLOAT3 dir(d.x, d.y, d.z);
	DirectX::XMVECTOR origin = DirectX::XMLoadFloat3(&ori);
	DirectX::XMVECTOR direction = DirectX::XMLoadFloat3(&dir);
	return cube->box.Intersects(origin, direction, dis);
}

void CollisionManager::rayCheck(const Vector3 & origin, const Vector3 & direction, BoundingCube * farthestCube, BoundingCube * nearestCube, float & farthestDis, float & nearestDis)
{
	float maxDis = -1.f, minDis = -1.f, dis = 0.f;
	for (std::vector<BoundingCube*>::iterator it = mBoundingCube.begin(); it != mBoundingCube.end(); it++) {
		if (collisionCheck(origin, direction, *it, dis)) {
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

void CollisionManager::rayCheckWithObstacle(const Vector3 & origin, const Vector3 & direction, const float & farthestDis, GameObject * gameobject, float & dis)
{
	float d = 0.f;
	for (std::vector<BoundingCube*>::iterator it = unmoveableBoundingCube.begin(); it != unmoveableBoundingCube.end(); it++) {
		if (collisionCheck(origin, direction, *it, d)) {
			if (gameobject == NULL && d < farthestDis) {
				dis = d;
				gameobject = (*it)->getObject();
			}
			else {
				if (d < dis) {
					dis = d;
					gameobject = (*it)->getObject();
				}
			}
		}
	}
}

bool CollisionManager::collisionCheck(const BoundingCube* cube1, const BoundingCube* cube2)
{
	//DirectX::XMVECTOR ori = DirectX::XMLoadFloat4(&cube1->box.Orientation);
	//ori = DirectX::XMVector4Normalize(ori);
	//DirectX::XMStoreFloat4(&(cube1->box.Orientation), ori);
	//ori = DirectX::XMLoadFloat4(&cube2->box.Orientation);
	//ori = DirectX::XMVector4Normalize(ori);
	//DirectX::XMStoreFloat4(&(cube2->box.Orientation), ori);
	return cube1->box.Intersects(cube2->box);
}

bool CollisionManager::collisionCheck(const BoundingCube * cube, const MBoundingSphere * sphere)
{
	return cube->box.Intersects(sphere->sphere);
}

void CollisionManager::deleteBoundingCube(const BoundingCube* cube)
{
	if (cube && mBoundingCube.size() > 0) {
		for (std::vector<BoundingCube*>::iterator it = mBoundingCube.begin(); it != mBoundingCube.end(); it++) {
			if (*it == cube) {
				mBoundingCube.erase(it);
				delete *it;
				*it = NULL;
			}
		}
	}
}

void CollisionManager::deleteBoundingSphere(const MBoundingSphere * sphere)
{
	if (sphere && mBoundingSphere.size() > 0) {
		for (std::vector<MBoundingSphere*>::iterator it = mBoundingSphere.begin(); it != mBoundingSphere.end(); it++) {
			if (*it == sphere) {
				mBoundingSphere.erase(it);
				delete *it;
				*it = NULL;
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
	for (std::vector<MBoundingSphere*>::iterator it = mBoundingSphere.begin(); it != mBoundingSphere.end(); it++) {
		if (*it) {
			delete *it;
			*it = NULL;
		}
	}
}
