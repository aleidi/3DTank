#include "Collision.h"
#include "DirectXCollision.h"

Collision::Collision() {
	mCube.reserve(50);
	mSphere.reserve(10);
	mRay.reserve(10);
	cubeNum = 0; sphereNum = 0; rayNum = 0;
}

Collision::Collision(const Collision&) {
}

Collision::~Collision() {
	mCube.shrink_to_fit();
	mSphere.shrink_to_fit();
	mRay.shrink_to_fit();
	cubeNum = sphereNum = rayNum = 0;
}

bool Collision::addCube(const Cube & cube) {
	mCube.push_back(cube);
	cubeNum++;
	return true;
}

bool Collision::addSphere(const Sphere & sphere)
{
	mSphere.push_back(sphere);
	sphereNum++;
	return true;
}

bool Collision::addRay(const Ray & ray)
{
	mRay.push_back(ray);
	rayNum++;
	return true;
}

bool Collision::deleteCube(const Cube & cube)
{
	if (cubeNum == 0) return false;
	if (mCube[cube.index] == cube) {
		std::vector<Cube>::iterator it = mCube.erase(mCube.begin() + cube.index);
		while (it != mCube.end()) { --(it->index); ++it; }
		cubeNum--;
		return true;
	}
	else
		return false;
}

bool Collision::deleteSphere(const Sphere & sphere)
{
	if (sphereNum == 0) return false;
	if (mSphere[sphere.index] == sphere) {
		std::vector<Sphere>::iterator it = mSphere.erase(mSphere.begin() + sphere.index);
		while (it != mSphere.end()) { --(it->index); ++it; }
		sphereNum--;
		return true;
	}
	else
		return false;
}

bool Collision::deleteRay(const Ray & ray)
{
	if (rayNum == 0) return false;
	if (mRay[ray.index] == ray) {
		std::vector<Ray>::iterator it = mRay.erase(mRay.begin() + ray.index);
		while (it != mRay.end()) { --(it->index); ++it; }
		rayNum--;
		return true;
	}
	else
		return false;
}

bool Collision::cubeCollisionCube(const Cube & cube1, const Cube & cube2)
{
	DirectX::XMFLOAT3 cen(cube1.center.x, cube1.center.y, cube1.center.z);
	DirectX::XMFLOAT3 ext(cube1.extents.x, cube1.extents.y, cube1.extents.z);
	DirectX::BoundingBox box1(cen, ext);
	cen.x = cube2.center.x; cen.y = cube2.center.y; cen.z = cube2.center.z;
	ext.x = cube2.extents.x; ext.y = cube2.extents.y; ext.z = cube2.extents.z;
	DirectX::BoundingBox box2(cen, ext);
	return box1.Intersects(box2);
}

bool Collision::cubeCollisionSphere(const Cube & cube, const Sphere & sph)
{
	DirectX::XMFLOAT3 cen(cube.center.x, cube.center.y, cube.center.z);
	DirectX::XMFLOAT3 ext(cube.extents.x, cube.extents.y, cube.extents.z);
	DirectX::BoundingBox box(cen, ext);
	cen.x = sph.center.x; cen.y = sph.center.y; cen.z = sph.center.z;
	DirectX::BoundingSphere sphere(cen, sph.radius);
	return box.Intersects(sphere);
}

bool Collision::cubeCollisionRay(const Cube& cube, const Ray& ray, float& dis)
{
	DirectX::XMFLOAT3 cen(cube.center.x, cube.center.y, cube.center.z);
	DirectX::XMFLOAT3 ext(cube.extents.x, cube.extents.y, cube.extents.z);
	DirectX::BoundingBox box(cen, ext);
	DirectX::FXMVECTOR ori{ ray.origin.x,ray.origin.y, ray.origin.z };
	DirectX::FXMVECTOR dir{ ray.direction.x,ray.direction.y, ray.direction.z };
	return box.Intersects(ori, dir, dis);
}

bool Collision::rayExamination(const Ray& ray, Cube& cube, float& dis)
{
	for (int i = 0; i < cubeNum; i++) {
		if (cubeCollisionRay(mCube[i], ray, dis) == true) {
			cube = mCube[i];
			return true;
		}
	}
	return false;
}

bool Collision::createCube(const Vector3& point1, const Vector3& point2)
{
	DirectX::BoundingBox out;
	DirectX::FXMVECTOR position1{ point1.x,point1.y,point1.z };
	DirectX::FXMVECTOR position2{ point2.x,point2.y,point2.z };
	DirectX::BoundingBox::CreateFromPoints(out, position1, position2);
	Vector3 cen(out.Center.x, out.Center.y, out.Center.z);
	Vector3 ext(out.Extents.x, out.Extents.y, out.Extents.z);
	Cube cube(cen, ext, cubeNum + 1);
	return addCube(cube);
}

bool Collision::createSphere(const Vector3& c, const float& r)
{
	Sphere sphere(c, r, sphereNum + 1);
	return addSphere(sphere);
}

bool Collision::createRay(const Vector3& o, const Vector3& d)
{
	Vector3 unit = d.normalize();
	Ray ray(o, unit, rayNum + 1);
	return addRay(ray);
}

void Collision::transformCube(Cube& cube, const float& scale, const Vector3& r, const Vector3 & t)
{
	DirectX::FXMVECTOR rotation{ r.x,r.y,r.z };
	DirectX::FXMVECTOR translation{ t.x,t.y,t.z };
	DirectX::XMFLOAT3 cen(cube.center.x, cube.center.y, cube.center.z);
	DirectX::XMFLOAT3 ext(cube.extents.x, cube.extents.y, cube.extents.z);
	DirectX::BoundingBox box(cen, ext);
	box.Transform(box, scale, rotation, translation);
	cube.center.x = box.Center.x; cube.center.y = box.Center.y; cube.center.z = box.Center.z;
	cube.extents.x = box.Extents.x; cube.extents.y = box.Extents.y; cube.extents.z = box.Extents.z;
}

void Collision::transformSphere(Sphere & sphere, const float & scale, const Vector3 & r, const Vector3 & t)
{
	DirectX::FXMVECTOR rotation{ r.x,r.y,r.z };
	DirectX::FXMVECTOR translation{ t.x,t.y,t.z };
	DirectX::XMFLOAT3 cen(sphere.center.x, sphere.center.y, sphere.center.z);
	DirectX::BoundingSphere sp(cen, sphere.radius);
	sp.Transform(sp, scale, rotation, translation);
	sphere.center.x = sp.Center.x; sphere.center.y = sp.Center.y; sphere.center.z = sp.Center.z;
	sphere.radius = sp.Radius;
}