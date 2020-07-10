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
	result = mChannel->isPlaying(&isPlaying);
	if (result == FMOD_OK)
		return;
	mFmodSound[0]->setMode(FMOD_LOOP_NORMAL);
	mFmodSystem->playSound(mFmodSound[0], NULL, false, &mChannel);
}

void SoundManager::playLoopAudio(const int & soundNum)
{
	bool isPlaying = false;
	FMOD_RESULT result;
	result = mChannel->isPlaying(&isPlaying);
	if (result == FMOD_OK)
		return;
	//mFmodSound[soundNum]->setMode(FMOD_LOOP_NORMAL);
	if (soundNum == 4) {
		mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &mSecondChannel);
	}
	else {
		mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &mChannel);
	}
}

void SoundManager::playOnceAudio(const int & soundNum)
{
	mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &mChannel);
}

void SoundManager::playOverlapSound(FMOD::Channel*& channel, int soundNum)
{
	mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &channel);
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

void SoundManager::setFrequency(const float & f, FMOD::Channel *& channel)
{
	channel->setFrequency(f);
}

void SoundManager::setPause(const int & soundNum)
{
	bool isPaused = false;
	FMOD_RESULT result;
	result = mChannel->getPaused(&isPaused);
	if (result != FMOD_OK) {
		return;
	}

	mChannel->setPaused(true);
	return;
}

void SoundManager::setReplay(const int & soundNum)
{
	bool isPaused = true;
	FMOD_RESULT result;
	result = mChannel->getPaused(&isPaused);
	if (result != FMOD_OK) {
		return;
	}

	mChannel->setPaused(false);
	return;
}

void SoundManager::setBGMValume(const float & valume)
{
	mChannel->setVolume(valume);
}

void SoundManager::setValume(const float & valume, FMOD::Channel *& channel)
{
	channel->setVolume(valume);
}

void SoundManager::setFrequency(const float & f)
{
	mChannel->setFrequency(f);
}

void SoundManager::stop(const int& soundNum)
{
	//bool isPlaying = false;
	//FMOD_RESULT result;
	//result = mChannel->isPlaying(&isPlaying);
	//if (result == FMOD_ERR_INVALID_HANDLE || result == FMOD_ERR_CHANNEL_STOLEN)
	//	return;
	if (soundNum == 4) {
		mSecondChannel->stop();
	}
	else {
		mChannel->stop();
	}
}

void SoundManager::stop(FMOD::Channel* channel)
{
	bool isPlaying = false;
	FMOD_RESULT result;
	result = channel->isPlaying(&isPlaying);
	if (result == FMOD_ERR_INVALID_HANDLE || result == FMOD_ERR_CHANNEL_STOLEN)
		return;

	channel->stop();
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
	mChannel->set3DAttributes(&position, NULL);
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
