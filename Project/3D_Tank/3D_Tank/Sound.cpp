#include "Sound.h"

Sound::Sound(){
}


Sound::~Sound(){
}

Sound::Sound(const Sound& other) {

}

bool Sound::initialize()
{
	FMOD_RESULT result;
	//init FMOD
	FMOD::System_Create(&mAudio);
	result = mAudio->init(100, FMOD_INIT_NORMAL, NULL);
	if (result != FMOD_OK) {
		return false;
	}

	//Load sound file
	/*for (int soundidx = 0; soundidx < SOUND_NUM; ++soundidx) {
		result = LoadSoundFile(SOUND_FILE_PATH[soundidx], soundidx);
		if (result != FMOD_OK) {
			return false;
		}
	}*/

	return true;
}

void Sound::playBGM(){
	FMOD_RESULT result;
	result = loadSoundFile(SOUND_FILE_PATH[0], 0);
	if (result != FMOD_OK)
		return;
	mSound[0]->setMode(FMOD_3D);
	mSound[0]->setMode(FMOD_LOOP_NORMAL);
	mAudio->playSound(mSound[0], NULL, false, &mChannel);
}

void Sound::play(const int& numberOfSoundFile) {
	switch (numberOfSoundFile) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	default:break;
	}


	mSound[1]->setMode(FMOD_3D);
	mAudio->playSound(mSound[1], NULL, false, NULL);
}

void Sound::stop(){
	mChannel->setPaused(true);
}

void Sound::shutDown() {
	mAudio->release();
}

FMOD_RESULT Sound::loadSoundFile(std::string filename, int soundidx){
	FMOD_RESULT result = FMOD_OK;
	const char* soundfilename = filename.c_str();
	
	result = mAudio->createStream(soundfilename, FMOD_DEFAULT, NULL, &mSound[soundidx]);
	//if (soundidx == 0) {
	//	//#define FMOD_LOOP_OFF 
	//	//#define FMOD_LOOP_NORMAL   
	//	mSound[0]->setMode(FMOD_LOOP_NORMAL);
	//	mAudio->playSound(mSound[0], NULL, false, &mChannel);
	//	
	//}
	return result;
}