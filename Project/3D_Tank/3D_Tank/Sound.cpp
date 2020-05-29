#include "Sound.h"

Sound::Sound() {
	FMOD::System_Create(&mFmodAudio);
}


Sound::~Sound() {
	mFmodAudio->close();
}

Sound::Sound(const Sound& other) {

}

bool Sound::onInit()
{
	FMOD_RESULT result;
	//init FMOD
	result = mFmodAudio->init(10, FMOD_INIT_NORMAL, NULL);
	if (result != FMOD_OK) {
		return false;
	}

	return true;
}

void Sound::playBGM() {
	bool isPlaying = false;
	FMOD_RESULT result;
	result = mFmodChannel[0]->isPlaying(&isPlaying);
	if (result == FMOD_OK)
		return;

	result = loadSoundFile(SOUND_FILE_PATH[0], 0);
	if (result != FMOD_OK)
		return;
	//mFmodSound[0]->setMode(FMOD_3D);
	setPosition();
	//mFmodSound[0]->setMode(FMOD_LOOP_NORMAL);
	mFmodAudio->playSound(mFmodSound[0], NULL, false, &mFmodChannel[0]);
}

void Sound::play(const int& numberOfSoundFile, const Vector3* position) {
	FMOD_RESULT result;
	bool isPlaying = false;
	switch (numberOfSoundFile) {
	case 0: {
		playBGM();
		break;
	}
	case 1: {
		result = mFmodChannel[numberOfSoundFile]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		result = loadSoundFile(SOUND_FILE_PATH[1], numberOfSoundFile);
		if (result != FMOD_OK)
			return;
		mFmodSound[1]->setMode(FMOD_3D);
		//setPosition(position, mFmodSound[1]);
		mFmodAudio->playSound(mFmodSound[1], NULL, false, &mFmodChannel[1]);
		break;
	}
	case 2: {
		result = mFmodChannel[numberOfSoundFile]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		result = loadSoundFile(SOUND_FILE_PATH[2], numberOfSoundFile);
		if (result != FMOD_OK)
			return;
		mFmodSound[2]->setMode(FMOD_3D);
		mFmodSound[2]->setMode(FMOD_LOOP_NORMAL);
		//setPosition(position, mFmodSound[2]);
		mFmodAudio->playSound(mFmodSound[2], NULL, false, &mFmodChannel[2]);
		break;
	}
	case 3: {
		result = mFmodChannel[numberOfSoundFile]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		result = loadSoundFile(SOUND_FILE_PATH[3], numberOfSoundFile);
		if (result != FMOD_OK)
			return;
		mFmodSound[3]->setMode(FMOD_3D);
		//setPosition(position, mFmodSound[3]);
		mFmodAudio->playSound(mFmodSound[3], NULL, false, &mFmodChannel[3]);
		break;
	}
	case 4: {
		result = mFmodChannel[numberOfSoundFile]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		result = loadSoundFile(SOUND_FILE_PATH[4], numberOfSoundFile);
		if (result != FMOD_OK)
			return;
		mFmodSound[4]->setMode(FMOD_3D);
		//setPosition(position, mFmodSound[4]);
		mFmodAudio->playSound(mFmodSound[4], NULL, false, &mFmodChannel[4]);
		break;
	}
	case 5: {
		result = mFmodChannel[numberOfSoundFile]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		result = loadSoundFile(SOUND_FILE_PATH[5], numberOfSoundFile);
		if (result != FMOD_OK)
			return;
		mFmodSound[5]->setMode(FMOD_3D);
		//setPosition(position, mFmodSound[5]);
		mFmodAudio->playSound(mFmodSound[5], NULL, false, &mFmodChannel[5]);
		break;
	}
	case 6: {
		result = mFmodChannel[numberOfSoundFile]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		result = loadSoundFile(SOUND_FILE_PATH[6], numberOfSoundFile);
		if (result != FMOD_OK)
			return;
		mFmodSound[6]->setMode(FMOD_3D);
		//setPosition(position, mFmodSound[6]);
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

void Sound::onUpdate(const float& f) {
	FMOD_VECTOR listenVector{ 10.0f + f,0.0f,0.0f };
	FMOD_VECTOR vel{ 1.0f,0.0f,0.0f };
	FMOD_VECTOR up{ 0.0f,1.0f,0.0f };
	FMOD_VECTOR forward{ 1.0f,0.0f,0.0f };
	mFmodAudio->set3DListenerAttributes(0, &listenVector, &vel, &forward, &up);
	mFmodAudio->update();
}
void Sound::shutDown() {
	mFmodAudio->release();
}

FMOD_RESULT Sound::loadSoundFile(std::string filename, int soundidx) {
	FMOD_RESULT result = FMOD_OK;
	const char* soundfilename = filename.c_str();
	result = mFmodAudio->createSound(soundfilename, FMOD_3D | FMOD_3D_LINEARROLLOFF, NULL, &mFmodSound[soundidx]);
	//	//#define FMOD_LOOP_OFF 
	//	//#define FMOD_LOOP_NORMAL   
	return result;
}

void Sound::setPosition() {
	FMOD_VECTOR position{ 0.0f,0.0f,0.0f };
	FMOD_VECTOR vel{ -1.0f,0.0f,0.0f };
	mFmodSound[0]->set3DMinMaxDistance(10.0f, 1000.0f);
	FMOD_VECTOR lin{ 1.0f,1.0f,1.0f };
	mFmodSound[0]->set3DCustomRolloff(&lin, 1);
	mFmodChannel[0]->set3DAttributes(&position, &vel);

}