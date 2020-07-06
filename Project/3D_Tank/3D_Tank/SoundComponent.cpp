#include "SoundComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Shell.h"
#include "ShellFlyComponent.h"

SoundComponent::SoundComponent(GameObject * obj) : Component(obj)
{
	//mChannel->set3DMinMaxDistance(10.f,20.f);
	mChannel->setMode(FMOD_3D_CUSTOMROLLOFF);
	FMOD_VECTOR points[3] = {
		{1.f,0.8f,0.f},
		{500.f,0.5f,0.f},
		{1000.f,0.1f,0.f}
	};
	mChannel->set3DCustomRolloff(points,3);
}

SoundComponent::~SoundComponent()
{
	//delete mChannel;
}

void SoundComponent::setPosition()
{
	Vector3 pos = this->getObject()->getTransform()->getPosition();
	if (pos.x == 0.f && pos.y == -3.f && pos.z == 0.f) {
		this->mChannel->set3DAttributes(&triggerPosition, NULL);
	}
	else {
		FMOD_VECTOR position;
		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;
		this->mChannel->set3DAttributes(&position, NULL);
	}
}

void SoundComponent::setPosition(const Vector3 & val)
{
	FMOD_VECTOR position;
	position.x = this->getObject()->getTransform()->getPosition().x;
	position.y = this->getObject()->getTransform()->getPosition().y;
	position.z = this->getObject()->getTransform()->getPosition().z;
	FMOD_VECTOR direction;
	direction.x = val.x; direction.y = val.y; direction.z = val.z;
	this->mChannel->set3DAttributes(&position, &direction);
}

void SoundComponent::setTriggerPosition(const Vector3 & pos)
{
	triggerPosition.x = pos.x;
	triggerPosition.y = pos.y;
	triggerPosition.z = pos.z;
}

void SoundComponent::onUpdate(float detalTime)
{
	Vector3 pos = this->getObject()->getTransform()->getPosition();
	if (pos.x == 0.f && pos.y == -3.f && pos.z == 0.f) {
		this->mChannel->set3DAttributes(&triggerPosition, NULL);
	}
	else {
		FMOD_VECTOR position;
		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;
		this->mChannel->set3DAttributes(&position, NULL);
	}
}
