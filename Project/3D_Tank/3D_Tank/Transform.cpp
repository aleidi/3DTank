#include "Transform.h"

Transform::Transform()
{
	forward = Vector3::forward;
	right = Vector3::right;
	up = Vector3::up;
}

void Transform::translate(Vector3 v)
{
	position += v;
}

void Transform::rotateX(float angle)
{
	rotation.x += angle;
}

void Transform::rotateY(float angle)
{
	rotation.y += angle;
}

void Transform::rotateZ(float angle)
{
	rotation.z += angle;
}

Transform* Transform::getChild(int index)
{
	return children.at(index);
}

void Transform::addParent(Transform* parent)
{
	this->parent = parent;
}

void Transform::addChild(Transform* child)
{
	children.push_back(child);
}