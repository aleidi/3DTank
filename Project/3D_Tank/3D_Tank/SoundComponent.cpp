#include "SoundComponent.h"
#include "GameObject.h"
#include "Transform.h"

SoundComponent::SoundComponent(GameObject * obj) : Component(obj)
{
}

SoundComponent::~SoundComponent()
{
}

//FMOD::Sound* SoundComponent::getSound()
//{
//	return this->mSound;
//}

void SoundComponent::onUpdate(float detalTime)
{
	FMOD_VECTOR position;
	position.x = this->getObject()->getTransform()->getPosition().x;
	position.y = this->getObject()->getTransform()->getPosition().y;
	position.z = this->getObject()->getTransform()->getPosition().z;
	this->mChannel->set3DAttributes(&position, NULL);
}

FMOD::Channel* SoundComponent::getChannel()
{
	return mChannel;
}

void SoundComponent::setChannel(FMOD::Channel * ch)
{
	if(ch)
		this->mChannel = ch;
}
