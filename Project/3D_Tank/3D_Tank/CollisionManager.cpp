#include "CollisionManager.h"
#include "BoundingCube.h"
#include "BoundingSphere.h"
#include "GameObject.h"
#include "Transform.h"

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

bool CollisionManager::collisionCheck_CubeToCube(const BoundingCube * cube, GameObject** obj)
{
	if (cube && mBoundingCube.size() > 0) {
		for (std::vector<BoundingCube*>::iterator it = mBoundingCube.begin(); it != mBoundingCube.end(); it++) {
			if (*it == cube) continue;
			if (collisionCheck(cube, *it) == true) {
				*obj = (*it)->getObject();
				return true;
			}
		}
		return false;
	}
	else
		return false;
}

bool CollisionManager::collisionCheck_SphereToCube(const MBoundingSphere * sphere, GameObject** obj)
{
	if (sphere != NULL) {
		for (std::vector<BoundingCube*>::iterator it = unmoveableBoundingCube.begin(); it != unmoveableBoundingCube.end(); it++) {
			if (collisionCheck(*it, sphere)) {
				*obj = (*it)->getObject();
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

bool CollisionManager::rayCheck(const Vector3 & origin, const Vector3 & direction, BoundingCube * farthestCube, BoundingCube * nearestCube, float & farthestDis, float & nearestDis)
{
	float dis = -1.f;
	for (std::vector<BoundingCube*>::iterator it = unmoveableBoundingCube.begin(); it != unmoveableBoundingCube.end(); it++) {
		if (collisionCheck(origin, direction, *it, dis)) {
			if (farthestCube == NULL && nearestCube == NULL) {
				farthestDis = nearestDis = dis;
				farthestCube = *it;
				nearestCube = *it;
			}
			else {
				if (dis > farthestDis) { farthestDis = dis; farthestCube = *it; }
				if (dis < nearestDis) { nearestDis = dis; nearestCube = *it; }
			}
			return true;
		}
	}
	return false;

}

bool CollisionManager::rayCheck(const Vector3 & origin, const Vector3 & direction, const float & farthestDis, GameObject * gameobject, float & dis)
{
	float d = -1.f;
	int flag = 0;
	for (std::vector<BoundingCube*>::iterator it = unmoveableBoundingCube.begin(); it != unmoveableBoundingCube.end(); it++) {
		if (collisionCheck(origin, direction, *it, dis)) {
			if (flag == 0) {

			}
		}
	}
	return true;
}

bool CollisionManager::rayCheckWithObstacle(const Vector3& origin, const Vector3& direction, const float& farthestDis, GameObject* gameobject, float& dis)
{
	float d = 0.f;
	int flag = 0;
	for (std::vector<BoundingCube*>::iterator it = unmoveableBoundingCube.begin(); it != unmoveableBoundingCube.end(); it++) {
		if (collisionCheck(origin, direction, *it, d)) {
			if (flag == 0 && d < farthestDis) {
				dis = d;
				gameobject = (*it)->getObject();
				flag++;
			}
			else {
				if (d < dis) {
					dis = d;
					gameobject = (*it)->getObject();
				}
			}
			return true;
		}
	}
	return false;
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
				delete *it;
				*it = NULL;
				mBoundingCube.erase(it);
				break;
			}
		}
		if (cube->moveable == 1) {
			for (std::vector<BoundingCube*>::iterator it = moveableBoundingCube.begin(); it != moveableBoundingCube.end(); it++) {
				if (*it == cube){
					delete *it;
					*it = NULL;
					moveableBoundingCube.erase(it);
					break;
				}
			}
		}
		else {
			for (std::vector<BoundingCube*>::iterator it = unmoveableBoundingCube.begin(); it != unmoveableBoundingCube.end(); it++) {
				if (*it == cube) {
					delete *it;
					*it = NULL;
					unmoveableBoundingCube.erase(it);
					break;
				}
			}
		}
	}
}

void CollisionManager::deleteBoundingSphere(const MBoundingSphere * sphere)
{
	if (sphere && mBoundingSphere.size() > 0) {
		for (std::vector<MBoundingSphere*>::iterator it = mBoundingSphere.begin(); it != mBoundingSphere.end(); it++) {
			if (*it == sphere) {
				delete *it;
				*it = NULL;
				mBoundingSphere.erase(it);
				break;
			}
		}
		if (sphere->moveable == 1) {
			for (std::vector<MBoundingSphere*>::iterator it = moveableBoundingSphere.begin(); it != moveableBoundingSphere.end(); it++) {
				if (*it == sphere) {
					delete *it;
					*it = NULL;
					moveableBoundingSphere.erase(it);
					break;
				}
			}
		}
		else {
			for (std::vector<MBoundingSphere*>::iterator it = unmoveableBoundingSphere.begin(); it != unmoveableBoundingSphere.end(); it++) {
				if (*it == sphere) {
					delete *it;
					*it = NULL;
					unmoveableBoundingSphere.erase(it);
					break;
				}
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

//void CollisionManager::onCollisionEnter(GameObject* obj)
//{
//	obj->onCollision = true;
//	if (obj->getTransform()->MoveDirection == 1)
//		obj->getTransform()->translate(obj->getTransform()->Forward*(0.01));
//	else
//		obj->getTransform()->translate(obj->getTransform()->Forward*(-0.01));
//	if (obj->getTransform()->RotateDirection == 1)
//		obj->getTransform()->rotateY(0.01);
//	else
//		obj->getTransform()->rotateY(-0.01);
//}
//
//void CollisionManager::onCollisionExit(GameObject * obj)
//{
//}
//
//void CollisionManager::onTriggerEnter(BoundingCube* cube1, BoundingCube* cube2)
//{
//	cube1->onTrigger = true;
//	cube2->onTrigger = true;
//}
//
//void CollisionManager::onTriggerExit(BoundingCube * cube1, BoundingCube * cube2)
//{
//	cube1->onTrigger = false;
//	cube2->onTrigger = false;
//}

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{
	for (std::vector<BoundingCube*>::iterator it = mBoundingCube.begin(); it != mBoundingCube.end(); it++) {
		if (*it) {
			delete *it; *it = NULL;
		}
	}
	for (std::vector<BoundingCube*>::iterator it = moveableBoundingCube.begin(); it != moveableBoundingCube.end(); it++) {
		if (*it) {
			delete *it; *it = NULL;
		}
	}
	for (std::vector<BoundingCube*>::iterator it = unmoveableBoundingCube.begin(); it != unmoveableBoundingCube.end(); it++) {
		if (*it) {
			delete *it; *it = NULL;
		}
	}
	for (std::vector<MBoundingSphere*>::iterator it = mBoundingSphere.begin(); it != mBoundingSphere.end(); it++) {
		if (*it) {
			delete *it; *it = NULL;
		}
	}
	for (std::vector<MBoundingSphere*>::iterator it = moveableBoundingSphere.begin(); it != moveableBoundingSphere.end(); it++) {
		if (*it) {
			delete *it; *it = NULL;
		}
	}
	for (std::vector<MBoundingSphere*>::iterator it = unmoveableBoundingSphere.begin(); it != unmoveableBoundingSphere.end(); it++) {
		if (*it) {
			delete *it; *it = NULL;
		}
	}
}
