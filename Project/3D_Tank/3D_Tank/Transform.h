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
	void onUpdate(float deltaTime) override;
	void onLateUpdate(float deltaTime) override;

	void translate(const Vector3&);
	void translate(float x, float y, float z);
	void rotateX(float, bool isDeg = true);
	void rotateY(float, bool isDeg = true);
	void rotateZ(float, bool isDeg = true);
	void rotate(float x, float y, float z, bool isDeg = true);

	Transform* getChild(int);
	Transform* getParent();
	void addParent(Transform*) noexcept;
	void addChild(Transform*) noexcept;
	bool removeChild(Transform* child) noexcept;
	bool removeParent() noexcept;

	Vector3 getPosition() noexcept;
	Vector3 getLocalPosition() noexcept;
	void setPosition(const Vector3& pos) noexcept;
	Vector3 getRotation() noexcept;
	Vector3 getLocalRotation() noexcept;
	void setRotation(const Vector3& rot) noexcept;
	Vector3 getScale() noexcept;
	Vector3 getLocalScale() noexcept;
	void setScale(const Vector3& scale) noexcept;
	void setScale(float x, float y, float z) noexcept;

	XMMATRIX getLocalToWorldMatrix() noexcept;
public:
	Vector3 Forward;
	Vector3 Right;
	Vector3 Up;
	int MoveDirection;   //0:forward, 1:back

private:
	void calcultateTransformMatrix() noexcept;
	void calculateRotForChildren(float angleX, float angleY, float angleZ) noexcept;

private:
	std::list<Transform*> children;
	Transform* parent;

	Vector3 mPosition;
	Vector3 mRotation;
	Vector3 mScale;
	XMFLOAT4X4 localToWorld;
};