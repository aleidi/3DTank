#include "Transform.h"

Transform::Transform(GameObject * obj) noexcept
	:Component(obj),
	Position(Vector3::zero),Rotation(Vector3::zero),Scale(Vector3::one),
	Forward(Vector3::forward),Right(Vector3::right),Up(Vector3::up),
	children(),parent()
{
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

DirectX::XMMATRIX Transform::getLoacalToWorldMatrix() noexcept
{
	if (parent != nullptr)
	{
		return parent->getLoacalToWorldMatrix()*
			DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z)*
			DirectX::XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z)*
			DirectX::XMMatrixTranslation(Position.x, Position.y, Position.z);
	}
	return DirectX::XMMatrixScaling(Scale.x,Scale.y,Scale.z)*
		DirectX::XMMatrixRotationRollPitchYaw(Rotation.x,Rotation.y,Rotation.z)*
		DirectX::XMMatrixTranslation(Position.x,Position.y,Position.z);
}
