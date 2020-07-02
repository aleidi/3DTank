#include "SoundComponent.h"
#include "GameObject.h"
#include "Transform.h"

SoundComponent::SoundComponent(GameObject * obj) : Component(obj)
{
	//mChannel->set3DMinMaxDistance(10.f,20.f);
	mChannel->setMode(FMOD_3D_CUSTOMROLLOFF);
	FMOD_VECTOR points[3] = {
		{1.f,0.8f,0.f},
		{20.f,0.5f,0.f},
		{50.f,0.2f,0.f}
	};
	mChannel->set3DCustomRolloff(points,3);
}

SoundComponent::~SoundComponent()
{
	//delete mChannel;
}

void SoundComponent::setPosition()
{
	FMOD_VECTOR position;
	position.x = this->getObject()->getTransform()->getPosition().x;
	position.y = this->getObject()->getTransform()->getPosition().y;
	position.z = this->getObject()->getTransform()->getPosition().z;
	this->mChannel->set3DAttributes(&position, NULL);
}

void SoundComponent::onUpdate(float detalTime)
{
	FMOD_VECTOR position;
	position.x = this->getObject()->getTransform()->getPosition().x;
	position.y = this->getObject()->getTransform()->getPosition().y;
	position.z = this->getObject()->getTransform()->getPosition().z;
	this->mChannel->set3DAttributes(&position, NULL);
}
