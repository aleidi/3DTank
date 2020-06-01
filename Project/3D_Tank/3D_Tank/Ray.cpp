#include "Ray.h"

Ray::Ray() :origin(0.f, 0.f, 0.f), direction(0.f, 0.f, 0.f) {}

Ray::Ray(const Vector3& ori, const Vector3& dir) : origin(ori), direction(dir) {

}

Ray::Ray(const Ray& other) : origin(other.origin), direction(other.direction) {
}

Ray::~Ray() {
}

Vector3 Ray::getOrigin() {
	return this->origin;
}

Vector3 Ray::getDirection() {
	return this->direction;
}