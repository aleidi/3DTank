#include "Transform.h"
#include "GameObject.h"

Transform::Transform(GameObject * obj) noexcept
	:Component(obj),
	Position(Vector3::zero),Rotation(Vector3::zero),Scale(Vector3::one),
	Forward(Vector3::forward),Right(Vector3::right),Up(Vector3::up),
	children(),parent(),
	localToWorld()
{
}

void Transform::onEngineUpdate(float deltaTime)
{
	calcultateTransformMatrix();

	for (std::list<Transform*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		if (*it != nullptr)
		{
			(*it)->getObject()->onEngineUpdate(deltaTime);
		}
	}
}

void Transform::onUpdate(float deltaTime)
{
	for (std::list<Transform*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		if (*it != nullptr)
		{
			(*it)->getObject()->onUpdate(deltaTime);
		}
	}
}

void Transform::translate(const Vector3& v)
{
	Position += v;
}

void Transform::translate(float x, float y, float z)
{
	Position.x += x;
	Position.y += y;
	Position.z += z;
}

void Transform::rotateX(float angle)
{
	Rotation.x += DirectX::XMConvertToRadians(angle);
}

void Transform::rotateY(float angle)
{
	Rotation.y += DirectX::XMConvertToRadians(angle);
}

void Transform::rotateZ(float angle)
{
	Rotation.z += DirectX::XMConvertToRadians(angle);
}

Transform* Transform::getChild(int index)
{
	std::list<Transform*>::iterator it = children.begin();
	for (int i = 0; i < index && it != children.end(); ++i)
	{
		if(index == i)
		{
			return *it;
		}
		++it;
	}
	return nullptr;
}

Transform * Transform::getParent()
{
	return parent;
}

void Transform::addParent(Transform* parent) noexcept
{
	this->parent = parent;
}

void Transform::addChild(Transform* child) noexcept
{
	children.push_back(child);
}

bool Transform::removeChild(Transform * child) noexcept
{
	for (std::list<Transform*>::iterator it = children.begin(); it != children.end();)
	{
		if (*it == child)
		{
			children.erase(it++);
			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

bool Transform::removeParent() noexcept
{
	if (nullptr == parent)
	{
		return false;
	}
	parent = nullptr;
	Position = worldPosition;
	Rotation = worldRotation;
	Scale = worldScale;
	return true;
}

XMMATRIX Transform::getLoacalToWorldMatrix() noexcept
{
	return XMLoadFloat4x4(&localToWorld);
}

void Transform::calcultateTransformMatrix() noexcept
{
	XMMATRIX matrix;
	XMVECTOR v;
	//calculate model->world matrix, world rotation and world scale
	if (parent != nullptr)
	{
		worldPosition =  parent->worldPosition + Position;
		worldRotation = parent->worldRotation + Rotation;
		worldScale = Vector3::multiply(parent->worldScale, Scale);
	}
	else
	{
		worldPosition = Position;
		worldRotation = Rotation;
		worldScale = Scale;
	}
	matrix = XMMatrixScaling(worldScale.x, worldScale.y, worldScale.z)*
		XMMatrixRotationRollPitchYaw(worldRotation.x, worldRotation.y, worldRotation.z)*
		XMMatrixTranslation(worldPosition.x, worldPosition.y, worldPosition.z);
	XMStoreFloat4x4(&localToWorld, matrix);

	//calculate forward vector of model
	v = XMVectorSet(Vector3::forward.x, Vector3::forward.y, Vector3::forward.z, 0.0f);
	v = XMVector4Transform(v, matrix);
	v = XMVector3Normalize(v);
	Forward.x = XMVectorGetX(v);
	Forward.y = XMVectorGetY(v);
	Forward.z = XMVectorGetZ(v);

	//calculate right vector of model
	v = XMVectorSet(Vector3::right.x, Vector3::right.y, Vector3::right.z, 0.0f);
	v = XMVector4Transform(v, matrix);
	v = XMVector3Normalize(v);
	Right.x = XMVectorGetX(v);
	Right.y = XMVectorGetY(v);
	Right.z = XMVectorGetZ(v);

	//calculate up vector of model
	v = XMVectorSet(Vector3::up.x, Vector3::up.y, Vector3::up.z, 0.0f);
	v = XMVector4Transform(v, matrix);
	v = XMVector3Normalize(v);
	Up.x = XMVectorGetX(v);
	Up.y = XMVectorGetY(v);
	Up.z = XMVectorGetZ(v);
}