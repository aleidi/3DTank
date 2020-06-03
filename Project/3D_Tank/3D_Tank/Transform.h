#pragma once
#include <list>

#include <DirectXMath.h>
#include "Component.h"
#include "Vector3.h"

using namespace DirectX;

class Transform : public Component
{
public:
	Transform(GameObject* obj) noexcept;
	void onUpdate(float deltaTime) override;

	void translate(Vector3);
	void translate(float x, float y, float z);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);

	Transform* getChild(int);
	void addParent(Transform*);
	void addChild(Transform*);
	
	XMMATRIX getLoacalToWorldMatrix() noexcept;

public:
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;
	Vector3 Forward;
	Vector3 Right;
	Vector3 Up;

	Vector3 worldPosition;
	Vector3 worldRotation;
	Vector3 worldScale;

private:
	std::list<Transform*> children;
	Transform* parent;

	XMFLOAT4X4 localToWorld;
};