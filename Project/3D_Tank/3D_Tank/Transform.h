#pragma once
#include <list>

#include <DirectXMath.h>
#include "Component.h"
#include "Vector3.h"

class Transform : Component
{
public:
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;
	Vector3 Forward;
	Vector3 Right;
	Vector3 Up;
protected:
	std::list<Transform*> children;
	Transform* parent;

	Vector3 worldPosition;
	Vector3 worldRotation;
	Vector3 worldScale;

public:
	Transform(GameObject* obj) noexcept;
	void translate(Vector3);
	void translate(float x, float y, float z);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);

	Transform* getChild(int);
	void addParent(Transform*);
	void addChild(Transform*);

	DirectX::XMMATRIX getLoacalToWorldMatrix() noexcept;
};