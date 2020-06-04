#pragma once
#include "Vector3.h"
#include <vector>

struct Cube {
	Vector3 center;
	Vector3 extents;
	int index;

	Cube() = default;
	Cube(const Vector3& cen, const Vector3& ext, const int& i) :center(cen), extents(ext), index(i) {}
	bool operator==(const Cube& cube) { return center == cube.center && extents == cube.extents && index == cube.index; }
};

struct Sphere {
	Vector3 center;
	float radius;
	int index;

	Sphere() = default;
	Sphere(const Vector3& cen, const float& r, const int& i) :center(cen), radius(r), index(i) {}
	bool operator==(const Sphere& sphere) { return center == sphere.center && radius == sphere.radius && index == sphere.index; }
};

struct Ray {
	Vector3 origin;
	Vector3 direction;
	int index;

	Ray() = default;
	Ray(const Vector3& o, const Vector3& d, const int& i) :origin(o), direction(d), index(i) {}
	bool operator==(const Ray& ray) { return origin == ray.origin && direction == ray.direction && index == ray.index; }
};

class Collision {
public:
	Collision();
	Collision(const Collision&);
	~Collision();

	bool addCube(const Cube& cube);
	bool addSphere(const Sphere& sphere);
	bool addRay(const Ray& ray);
	bool deleteCube(const Cube& cube);
	bool deleteSphere(const Sphere& sphere);
	bool deleteRay(const Ray& ray);

	bool cubeCollisionCube(const Cube& cube1, const Cube& cube2);
	bool cubeCollisionSphere(const Cube& cube, const Sphere& sph);
	bool cubeCollisionRay(const Cube& cube, const Ray& ray, float& dis);
	bool rayExamination(const Ray& ray, Cube& cube, float& dis);

	bool createCube(const Vector3& point1, const Vector3& point2);//pt1和pt2可以是包围盒某一对角线上的两个顶点，也可以是所有点中xyz分量中最大值和最小值的两个构造点
	bool createSphere(const Vector3& c, const float& r);
	bool createRay(const Vector3& o, const Vector3& d); //the direction of ray is unit vector

	void transformCube(Cube& cube, const float& scale, const Vector3& r, const Vector3& t);
	void transformSphere(Sphere& sphere, const float& scale, const Vector3& r, const Vector3& t);
	void onUpdate();

	std::vector<Cube>mCube;
	std::vector<Sphere>mSphere;
	std::vector<Ray>mRay;

private:
	//std::vector<Cube>mCube;
	//std::vector<Sphere>mSphere;
	//std::vector<Ray>mRay;

	int cubeNum;
	int sphereNum;
	int rayNum;
};