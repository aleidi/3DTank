#include "Sound.h"

Sound::Sound() {
}


Sound::~Sound() {
}

Sound::Sound(const Sound& other) {

}

bool Sound::initialize()
{
	FMOD_RESULT result;
	//init FMOD
	FMOD::System_Create(&mFmodAudio);
	result = mFmodAudio->init(100, FMOD_INIT_NORMAL, NULL);
	if (result != FMOD_OK) {
		return false;
	}

	return true;
}

void Sound::playBGM() {

	FMOD_RESULT result;
	result = loadSoundFile(SOUND_FILE_PATH[0], 0);
	if (result != FMOD_OK)
		return;
	mFmodSound[0]->setMode(FMOD_3D);
	//mFmodSound[0]->setMode(FMOD_LOOP_NORMAL);
	mFmodAudio->playSound(mFmodSound[0], NULL, false, &mFmodChannel[0]);
}

void Sound::play(const int& numberOfSoundFile, const Vector3* position) {
	FMOD_RESULT result;
	switch (numberOfSoundFile) {
	case 0: {
		playBGM();
		break;
	}
	case 1: {
		result = loadSoundFile(SOUND_FILE_PATH[1], numberOfSoundFile);
		if (result != FMOD_OK)
			return;
		mFmodSound[1]->setMode(FMOD_3D);
		setPosition(position, mFmodSound[1]);
		mFmodAudio->playSound(mFmodSound[1], NULL, false, &mFmodChannel[1]);
		break;
	}
	case 2: {
		result = loadSoundFile(SOUND_FILE_PATH[2], numberOfSoundFile);
		if (result != FMOD_OK)
			return;
		mFmodSound[2]->setMode(FMOD_3D);
		mFmodSound[2]->setMode(FMOD_LOOP_NORMAL);
		setPosition(position, mFmodSound[2]);
		mFmodAudio->playSound(mFmodSound[2], NULL, false, &mFmodChannel[2]);
		break;
	}
	case 3: {
		result = loadSoundFile(SOUND_FILE_PATH[3], numberOfSoundFile);
		if (result != FMOD_OK)
			return;
		mFmodSound[3]->setMode(FMOD_3D);
		setPosition(position, mFmodSound[3]);
		mFmodAudio->playSound(mFmodSound[3], NULL, false, &mFmodChannel[3]);
		break;
	}
	case 4: {
		result = loadSoundFile(SOUND_FILE_PATH[4], numberOfSoundFile);
		if (result != FMOD_OK)
			return;
		mFmodSound[4]->setMode(FMOD_3D);
		setPosition(position, mFmodSound[4]);
		mFmodAudio->playSound(mFmodSound[4], NULL, false, &mFmodChannel[4]);
		break;
	}
	case 5: {
		result = loadSoundFile(SOUND_FILE_PATH[5], numberOfSoundFile);
		if (result != FMOD_OK)
			return;
		mFmodSound[5]->setMode(FMOD_3D);
		setPosition(position, mFmodSound[5]);
		mFmodAudio->playSound(mFmodSound[5], NULL, false, &mFmodChannel[5]);
		break;
	}
	case 6: {
		result = loadSoundFile(SOUND_FILE_PATH[6], numberOfSoundFile);
		if (result != FMOD_OK)
			return;
		mFmodSound[6]->setMode(FMOD_3D);
		setPosition(position, mFmodSound[6]);
		mFmodAudio->playSound(mFmodSound[6], NULL, false, &mFmodChannel[6]);
		break;
	}
	default:break;
	}
}

bool Sound::setPause(const int& numOfChannel) {
	bool isPaused = false;
	FMOD_RESULT result;
	result = mFmodChannel[numOfChannel]->getPaused(&isPaused);
	if (result != FMOD_OK) {
		return false;
	}

	mFmodChannel[numOfChannel]->setPaused(true);
	return true;
}

bool Sound::setReplay(const int& numOfChannel) {
	bool isPaused = true;
	FMOD_RESULT result;
	result = mFmodChannel[numOfChannel]->getPaused(&isPaused);
	if (result != FMOD_OK) {
		return false;
	}

	mFmodChannel[numOfChannel]->setPaused(false);
	return true;
}

bool Sound::stop(const int& numOfChannel) {
	bool isPlaying = false;
	FMOD_RESULT result;
	result = mFmodChannel[numOfChannel]->isPlaying(&isPlaying);
	if (result == FMOD_ERR_INVALID_HANDLE || result == FMOD_ERR_CHANNEL_STOLEN)
		return false;

	mFmodChannel[numOfChannel]->stop();
	return true;
}

void Sound::shutDown() {
	mFmodAudio->release();
}

FMOD_RESULT Sound::loadSoundFile(std::string filename, int soundidx) {
	FMOD_RESULT result = FMOD_OK;
	const char* soundfilename = filename.c_str();

	result = mFmodAudio->createStream(soundfilename, FMOD_DEFAULT, NULL, &mFmodSound[soundidx]);
	//if (soundidx == 0) {
	//	//#define FMOD_LOOP_OFF 
	//	//#define FMOD_LOOP_NORMAL   
	//	mSound[0]->setMode(FMOD_LOOP_NORMAL);
	//	mAudio->playSound(mSound[0], NULL, false, &mChannel);
	//	
	//}
	return result;
}

void Sound::setPosition(const Vector3* mVector, FMOD::Sound* mFmodSound) {
	FMOD_VECTOR fVector;
	fVector.x = mVector->x;
	fVector.y = mVector->y;
	fVector.z = mVector->z;
	mFmodSound->set3DCustomRolloff(&fVector, 2);
}