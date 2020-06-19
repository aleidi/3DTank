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

	//void playSound();
	//void setPause();
	//void setReplay();
	void onUpdate();
	FMOD::Sound* getSound();
	FMOD::Channel* getChannel();

	//FMOD_RESULT loadSoundFile(const std::string& filePath);

private:
	//friend class SoundManager;

	FMOD::Sound* mSound;
	FMOD::Channel* mChannel;
};