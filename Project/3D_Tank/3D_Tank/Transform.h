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
	void onEngineUpdate(float deltaTime) override;

	void translate(const Vector3&);
	void translate(float x, float y, float z);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);

	Transform* getChild(int);
	Transform* getParent();
	void addParent(Transform*) noexcept;
	void addChild(Transform*) noexcept;
	bool removeChild(Transform* child) noexcept;
	bool removeParent() noexcept;

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
	void calcultateTransformMatrix() noexcept;

private:
	std::list<Transform*> children;
	Transform* parent;

	XMFLOAT4X4 localToWorld;
};