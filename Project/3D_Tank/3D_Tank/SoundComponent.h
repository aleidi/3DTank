#pragma once
#include <string>
#include "fmod/fmod.hpp"
#include "fmod/fmod.h"
#include "Vector3.h"
#include "Component.h"

#ifdef _DEBUG
#pragma comment(lib,"fmodL_vc.lib")
#else
#pragma comment(lib,"fmod_vc.lib")
#endif

class SoundComponent : public Component {
public:
	SoundComponent(GameObject* obj);
	~SoundComponent();

	void setPosition();
	void setPosition(const Vector3& val);
	void setTriggerPosition(const Vector3& pos);
	void onUpdate(const float& detalTime) override;

	FMOD_VECTOR triggerPosition;
	FMOD::Channel* mChannel;
};