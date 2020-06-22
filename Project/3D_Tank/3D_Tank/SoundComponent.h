#pragma once
#include <string>
#include "fmod/fmod.hpp"
#include "fmod/fmod.h"
#include "Vector3.h"
#include "Component.h"

#pragma comment (lib,"fmod_vc.lib")
#pragma comment (lib,"fmodL_vc.lib")

class SoundComponent : public Component {
public:
	SoundComponent(GameObject* obj);
	~SoundComponent();

	void setPosition();
	void onUpdate(float detalTime) override;

	FMOD::Channel* mChannel;
};