#include "Transform.h"

Transform::Transform(GameObject * obj) noexcept
	:Component(obj),
	Position(Vector3::zero),Rotation(Vector3::zero),Scale(Vector3::one),
	Forward(Vector3::forward),Right(Vector3::right),Up(Vector3::up),
	children(),parent(),
	localToWorld()
{
}

void Transform::onUpdate(float deltaTime)
{
	XMMATRIX matrix;
	//calculate model->world matrix
	if (parent != nullptr)
	{
		matrix = parent->getLoacalToWorldMatrix()*
			XMMatrixScaling(Scale.x, Scale.y, Scale.z)*
			XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z)*
			XMMatrixTranslation(Position.x, Position.y, Position.z);
	}
	else
	{
		matrix = XMMatrixScaling(Scale.x, Scale.y, Scale.z)*
			XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z)*
			XMMatrixTranslation(Position.x, Position.y, Position.z);
	}
	XMStoreFloat4x4(&localToWorld, matrix);
	
	//calculate world position
	XMVECTOR v = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	v = XMVector3Transform(v, matrix);
	worldPosition.x = XMVectorGetX(v);
	worldPosition.y = XMVectorGetY(v);
	worldPosition.z = XMVectorGetZ(v);


	//calculate forward vector of model
	v = XMVectorSet(Vector3::forward.x, Vector3::forward.y, Vector3::forward.z, 0.0f);
	v = XMVector3Transform(v, matrix);
	v = XMVector3Normalize(v);
	Forward.x = XMVectorGetX(v);
	Forward.y = XMVectorGetY(v);
	Forward.z = XMVectorGetZ(v);

	//calculate right vector of model
	v = XMVectorSet(Vector3::right.x, Vector3::right.y, Vector3::right.z, 0.0f);
	v = XMVector3Transform(v, matrix);
	v = XMVector3Normalize(v);
	Right.x = XMVectorGetX(v);
	Right.y = XMVectorGetY(v);
	Right.z = XMVectorGetZ(v);

	//calculate up vector of model
	v = XMVectorSet(Vector3::up.x, Vector3::up.y, Vector3::up.z, 0.0f);
	v = XMVector3Transform(v, matrix);
	v = XMVector3Normalize(v);
	Up.x = XMVectorGetX(v);
	Up.y = XMVectorGetY(v);
	Up.z = XMVectorGetZ(v);
}

void Transform::translate(Vector3 v)
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

void Transform::addParent(Transform* parent)
{
	this->parent = parent;
}

void Transform::addChild(Transform* child)
{
	children.push_back(child);
}

XMMATRIX Transform::getLoacalToWorldMatrix() noexcept
{
	return XMLoadFloat4x4(&localToWorld);
}