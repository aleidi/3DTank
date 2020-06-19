#include "SoundComponent.h"
#include "GameObject.h"
#include "Transform.h"

SoundComponent::SoundComponent(GameObject * obj) : Component(obj)
{
}

SoundComponent::~SoundComponent()
{
}

void SoundComponent::onUpdate()
{
	FMOD_VECTOR position;
	position.x = this->getObject()->getTransform()->getPosition().x;
	position.y = this->getObject()->getTransform()->getPosition().y;
	position.z = this->getObject()->getTransform()->getPosition().z;
	this->mChannel->set3DAttributes(&position, NULL);
}

FMOD::Sound* SoundComponent::getSound()
{
	return this->mSound;
}

FMOD::Channel* SoundComponent::getChannel()
{
	return this->mChannel;
}
