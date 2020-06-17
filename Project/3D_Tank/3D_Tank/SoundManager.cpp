#include "SoundManager.h"

SoundManager* SoundManager::sInstance = NULL;

SoundManager * SoundManager::sGetInstance()
{
	if (sInstance == NULL)
		sInstance = new SoundManager();
	return sInstance;
}

void SoundManager::onInit()
{
	if (sInstance != NULL) {
		sInstance = NULL;
		sInstance = new SoundManager();
	}
	else {
		sInstance = new SoundManager();
	}

}

void SoundManager::playBGM()
{
	bool isPlaying = false;
	FMOD_RESULT result;
	result = mFmodChannel[0]->isPlaying(&isPlaying);
	if (result == FMOD_OK)
		return;

	result = loadSoundFile(SOUND_FILE_PATH[0], 0);
	if (result != FMOD_OK)
		return;
	//mFmodSound[0]->setMode(FMOD_LOOP_NORMAL);
	mFmodSystem->playSound(mFmodSound[0], NULL, false, &mFmodChannel[0]);
}

void SoundManager::playSound(const int & soundNum)
{
	FMOD_RESULT result;
	bool isPlaying = false;
	switch (soundNum) {
	case 0: {
		playBGM();
		break;
	}
	case 1: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		result = loadSoundFile(SOUND_FILE_PATH[1], soundNum);
		if (result != FMOD_OK)
			return;
		mFmodSound[1]->setMode(FMOD_3D);
		mFmodSystem->playSound(mFmodSound[1], NULL, false, &mFmodChannel[1]);
		break;
	}
	case 2: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		result = loadSoundFile(SOUND_FILE_PATH[2], soundNum);
		if (result != FMOD_OK)
			return;
		mFmodSound[2]->setMode(FMOD_3D);
		mFmodSystem->playSound(mFmodSound[2], NULL, false, &mFmodChannel[2]);
		break;
	}
	case 3: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		result = loadSoundFile(SOUND_FILE_PATH[3], soundNum);
		if (result != FMOD_OK)
			return;
		mFmodSound[3]->setMode(FMOD_3D);
		mFmodSystem->playSound(mFmodSound[3], NULL, false, &mFmodChannel[3]);
		break;
	}
	case 4: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		result = loadSoundFile(SOUND_FILE_PATH[4], soundNum);
		if (result != FMOD_OK)
			return;
		mFmodSound[4]->setMode(FMOD_3D);
		mFmodSystem->playSound(mFmodSound[4], NULL, false, &mFmodChannel[4]);
		break;
	}
	case 5: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		result = loadSoundFile(SOUND_FILE_PATH[5], soundNum);
		if (result != FMOD_OK)
			return;
		mFmodSound[5]->setMode(FMOD_3D);
		mFmodSystem->playSound(mFmodSound[5], NULL, false, &mFmodChannel[5]);
		break;
	}
	case 6: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		result = loadSoundFile(SOUND_FILE_PATH[6], soundNum);
		if (result != FMOD_OK)
			return;
		mFmodSound[6]->setMode(FMOD_3D);
		mFmodSystem->playSound(mFmodSound[6], NULL, false, &mFmodChannel[6]);
		break;
	}
	default:break;
	}
}

void SoundManager::setPause(const int & soundNum)
{
	bool isPaused = false;
	FMOD_RESULT result;
	result = mFmodChannel[soundNum]->getPaused(&isPaused);
	if (result != FMOD_OK) {
		return;
	}

	mFmodChannel[soundNum]->setPaused(true);
	return;
}

void SoundManager::setReplay(const int & soundNum)
{
	bool isPaused = true;
	FMOD_RESULT result;
	result = mFmodChannel[soundNum]->getPaused(&isPaused);
	if (result != FMOD_OK) {
		return;
	}

	mFmodChannel[soundNum]->setPaused(false);
	return;
}

void SoundManager::stop(const int & soundNum)
{
	bool isPlaying = false;
	FMOD_RESULT result;
	result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
	if (result == FMOD_ERR_INVALID_HANDLE || result == FMOD_ERR_CHANNEL_STOLEN)
		return;

	mFmodChannel[soundNum]->stop();
	return;
}

void SoundManager::onUpdate()
{
	mFmodSystem->update();
}

void SoundManager::setSoundPosAndVel(const Vector3 & pos, const Vector3 & vel, const int & soundNum)
{
	FMOD_VECTOR position;
	position.x = pos.x; position.y = pos.y; position.z = pos.z;
	FMOD_VECTOR velocity;
	velocity.x = vel.x; velocity.y = vel.y; velocity.z = vel.z;
	mFmodSound[soundNum]->set3DMinMaxDistance(5.f, 1000.f);
	mFmodChannel[soundNum]->set3DAttributes(&position, &velocity);
}

void SoundManager::setLisenterPosition(const Vector3 & pos)
{
	FMOD_VECTOR listenerPos;
	listenerPos.x = pos.x; listenerPos.y = pos.y; listenerPos.z = pos.z;
	mFmodSystem->set3DListenerAttributes(0, &listenerPos, 0, 0, 0);
}

FMOD_RESULT SoundManager::loadSoundFile(const std::string & filepath, const int & soundNum)
{
	FMOD_RESULT result = FMOD_OK;
	const char* soundfilename = filepath.c_str();
	result = mFmodSystem->createSound(soundfilename, FMOD_3D, NULL, &mFmodSound[soundNum]);
	//	//#define FMOD_LOOP_OFF 
	//	//#define FMOD_LOOP_NORMAL   
	return result;
}

SoundManager::SoundManager()
{
	FMOD::System_Create(&mFmodSystem);
	mFmodSystem->init(10, FMOD_INIT_NORMAL, NULL);
}

SoundManager::~SoundManager()
{
	mFmodSystem->close();
}