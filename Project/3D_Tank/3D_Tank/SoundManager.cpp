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

void SoundManager::destory()
{
	delete sInstance;
	sInstance = NULL;
}

void SoundManager::playBGM()
{
	bool isPlaying = false;
	FMOD_RESULT result;
	result = mFmodChannel[0]->isPlaying(&isPlaying);
	if (result == FMOD_OK)
		return;
	mFmodSound[0]->setMode(FMOD_LOOP_NORMAL);
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

		mFmodSystem->playSound(mFmodSound[1], NULL, false, &mFmodChannel[1]);
		break;
	}
	case 2: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		mFmodSystem->playSound(mFmodSound[2], NULL, false, &mFmodChannel[2]);
		break;
	}
	case 3: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		mFmodSystem->playSound(mFmodSound[3], NULL, false, &mFmodChannel[3]);
		break;
	}
	case 4: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		mFmodSystem->playSound(mFmodSound[4], NULL, false, &mFmodChannel[4]);
		break;
	}
	case 5: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		mFmodSystem->playSound(mFmodSound[5], NULL, false, &mFmodChannel[5]);
		break;
	}
	case 6: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		mFmodSystem->playSound(mFmodSound[6], NULL, false, &mFmodChannel[6]);
		break;
	}
	case 7: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &mFmodChannel[soundNum]);
		break;
	}
	case 8: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &mFmodChannel[soundNum]);
		break;
	}
	case 9: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &mFmodChannel[soundNum]);
		break;
	}
	case 10: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &mFmodChannel[soundNum]);
		break;
	}
	case 11: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &mFmodChannel[soundNum]);
		break;
	}
	case 12: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &mFmodChannel[soundNum]);
		break;
	}
	case 13: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &mFmodChannel[soundNum]);
		break;
	}
	default:break;
	}
}

void SoundManager::playOverlapSound(FMOD::Channel*& channel, int soundNum)
{
	mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &mFmodChannel[soundNum]);
	//mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &channel);
}

void SoundManager::playSingleSound(FMOD::Channel *& channel, int soundNum)
{
	bool isPlaying = false;
	FMOD_RESULT result;
	result = channel->isPlaying(&isPlaying);
	if (result == FMOD_OK)
		return;
	mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &channel);
}

void SoundManager::setPause(FMOD::Channel *& channel)
{
	bool isPaused = false;
	FMOD_RESULT result;
	result = channel->getPaused(&isPaused);
	if (result != FMOD_OK)
		return;
	channel->setPaused(true);
}

void SoundManager::setReplay(FMOD::Channel *& channel)
{
	bool isPaused = true;
	FMOD_RESULT result;
	result = channel->getPaused(&isPaused);
	if (result != FMOD_OK)
		return;
	channel->setPaused(false);
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

void SoundManager::setBGMValume(const float & valume)
{
	mFmodChannel[0]->setVolume(valume);
}

void SoundManager::setValume(const float & valume, FMOD::Channel *& channel)
{
	channel->setVolume(valume);
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

void SoundManager::stop(FMOD::Channel* channel)
{
	bool isPlaying = false;
	FMOD_RESULT result;
	result = channel->isPlaying(&isPlaying);
	if (result == FMOD_ERR_INVALID_HANDLE || result == FMOD_ERR_CHANNEL_STOLEN)
		return;

	channel->stop();
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
	//mFmodSound[soundNum]->set3DMinMaxDistance(5.f, 1000.f);
	mFmodChannel[soundNum]->set3DAttributes(&position, NULL);
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

FMOD_RESULT SoundManager::loadALLSoundFile()
{
	FMOD_RESULT result = FMOD_OK;
	for (int i = 0; i < SOUND_NUM; i++) {
		const char* soundfilename = SOUND_FILE_PATH[i].c_str();
		result = mFmodSystem->createSound(soundfilename, FMOD_3D, NULL, &mFmodSound[i]);
		if (result != FMOD_OK) return result;
		if (i == 0) mFmodSound[0]->setMode(FMOD_LOOP_NORMAL);
		if (i == 2) {
			mFmodSound[i]->set3DMinMaxDistance(20.f, 50.f);
		}
		else {
			mFmodSound[i]->set3DMinMaxDistance(10.f, 1000.f);
		}
	}
	//	//#define FMOD_LOOP_OFF
	//	//#define FMOD_LOOP_NORMAL
	return result;
}

SoundManager::SoundManager()
{
	FMOD::System_Create(&mFmodSystem);
	mFmodSystem->init(100, FMOD_INIT_NORMAL, NULL);
	loadALLSoundFile();
}

SoundManager::~SoundManager()
{
	mFmodSystem->close();
}
