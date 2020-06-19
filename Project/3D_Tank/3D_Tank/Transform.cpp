#include "Transform.h"
#include "GameObject.h"

Transform::Transform(GameObject * obj) noexcept
	:Component(obj),
	mPosition(Vector3::zero), mRotation(Vector3::zero), mScale(Vector3::one),
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
	mPosition += v;
	if (this->getObject()->cube != NULL && this->getObject()->cube->moveable == 1) {
		this->getObject()->cube->box.Center.x += v.x;
		this->getObject()->cube->box.Center.y += v.y;
		this->getObject()->cube->box.Center.z += v.z;
	}
}

void Transform::translate(float x, float y, float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
}

void Transform::rotateX(float angle, bool isDeg)
{
	if (isDeg == false)
	{
		mRotation.x += angle;
	}
	else
	{
		mRotation.x += DirectX::XMConvertToRadians(angle);
	}
}

void Transform::rotateY(float angle, bool isDeg)
{
	if (isDeg == false)
	{
		mRotation.y += angle;
	}
	else
	{
		mRotation.y += DirectX::XMConvertToRadians(angle);
	}
	if (this->getObject()->cube != NULL && this->getObject()->cube->moveable == 1) {
		DirectX::XMStoreFloat4(&(this->getObject()->cube->box.Orientation),
			DirectX::XMQuaternionRotationRollPitchYaw(
				this->getObject()->getTransform()->getRotation().x,
				this->getObject()->getTransform()->getRotation().y,
				this->getObject()->getTransform()->getRotation().z
			)
		);
	}
}

void Transform::rotateZ(float angle, bool isDeg)
{
	if (isDeg == false)
	{
		mRotation.z += angle;
	}
	else
	{
		mRotation.z += DirectX::XMConvertToRadians(angle);
	}
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
	mPosition += parent->getPosition();
	mRotation += parent->getRotation();
	mScale *= parent->getScale();
	parent = nullptr;
	return true;
}

Vector3 Transform::getPosition() noexcept
{
	if (parent != nullptr)
	{
		return parent->getPosition() + mPosition;
	}
	return mPosition;
}

Vector3 Transform::getLocalPosition() noexcept
{
	return mPosition;
}

void Transform::setPosition(const Vector3 & pos) noexcept
{
	if (parent != nullptr)
	{
		mPosition = pos - parent->getPosition();
		return;
	}
	mPosition = pos;
}

Vector3 Transform::getRotation() noexcept
{
	if (parent != nullptr)
	{
		return parent->getRotation() + mRotation;
	}
	return mRotation;
}

Vector3 Transform::getLocalRotation() noexcept
{
	return mRotation;
}

void Transform::setRotation(const Vector3 & rot) noexcept
{
	if (parent != nullptr)
	{
		mRotation = rot - parent->getRotation();
		return;
	}
	mRotation = rot;
}

Vector3 Transform::getScale() noexcept
{
	if (parent != nullptr)
	{
		return Vector3::multiply(parent->getScale(), mScale);
	}
	return mScale;
}

Vector3 Transform::getLocalScale() noexcept
{
	return mScale;
}

void Transform::setScale(const Vector3 & scale) noexcept
{
	if (parent != nullptr)
	{
		mScale = scale / parent->getScale();
		return;
	}
	mScale = scale;
}

void Transform::setScale(float x, float y, float z) noexcept
{
	if (parent != nullptr)
	{
		Vector3 ps = parent->getScale();
		mScale.x = x / ps.x;
		mScale.y = y / ps.y;
		mScale.z = z / ps.z;
		return;
	}
	mScale.x = x;
	mScale.y = y;
	mScale.z = z;
}

XMMATRIX Transform::getLocalToWorldMatrix() noexcept
{
	return XMLoadFloat4x4(&localToWorld);
}

void Transform::calcultateTransformMatrix() noexcept
{
	//calculate model->world matrix, world rotation and world scale
	Vector3 pos;
	Vector3 rot;
	Vector3 scale;
	XMMATRIX matrix;

	if (parent != nullptr)
	{
		pos =  parent->getPosition() + mPosition;
		rot = parent->getRotation() + mRotation;
		scale = Vector3::multiply(parent->getScale(), mScale);
		matrix = XMMatrixScaling(scale.x, scale.y, scale.z)*
			XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z)*
			XMMatrixTranslation(pos.x, pos.y, pos.z);
	}
	else
	{
		pos = mPosition;
		rot = mRotation;
		scale = mScale;
	}
	matrix = XMMatrixScaling(scale.x, scale.y, scale.z)*
		XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z)*
		XMMatrixTranslation(pos.x, pos.y, pos.z);
	XMStoreFloat4x4(&localToWorld, matrix);

	XMVECTOR v;
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