#pragma once
#include <vector>

#include "Component.h"
#include "Vector3.h"

class Transform : Component
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Vector3 forward;
	Vector3 right;
	Vector3 up;
protected:
	std::vector<Transform*> children;
	Transform* parent;

	Vector3 worldPosition;
	Vector3 worldRotation;
	Vector3 worldScale;
	//	Matrix4x4 localToWorldMatrix;
	//	Matrix4x4 worldToLocalMatrix;

public:
	Transform();
	void translate(Vector3);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);

	Transform* getChild(int);
	void addParent(Transform*);
	void addChild(Transform*);

	//	void setWorldToLocalMatrix();
	//	Matrix4x4 getWorldToLocalMatrix();
	//	void setLocalToWorldMatrix();
	//	Matrix4x4 getLocalToWorldMatrix();
};