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

	//result = loadSoundFile(SOUND_FILE_PATH[0], 0);
	//if (result != FMOD_OK)
	//	return;
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

		/*result = loadSoundFile(SOUND_FILE_PATH[1], soundNum);
		if (result != FMOD_OK)
			return;*/
		//mFmodSound[1]->setMode(FMOD_3D);
		mFmodSystem->playSound(mFmodSound[1], NULL, false, &mFmodChannel[1]);
		break;
	}
	case 2: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		/*result = loadSoundFile(SOUND_FILE_PATH[2], soundNum);
		if (result != FMOD_OK)
			return;*/
		//mFmodSound[2]->setMode(FMOD_3D);
		mFmodSystem->playSound(mFmodSound[2], NULL, false, &mFmodChannel[2]);
		break;
	}
	case 3: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		/*result = loadSoundFile(SOUND_FILE_PATH[3], soundNum);
		if (result != FMOD_OK)
			return;*/
		//mFmodSound[3]->setMode(FMOD_3D);
		mFmodSystem->playSound(mFmodSound[3], NULL, false, &mFmodChannel[3]);
		break;
	}
	case 4: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		/*result = loadSoundFile(SOUND_FILE_PATH[4], soundNum);
		if (result != FMOD_OK)
			return;*/
		//mFmodSound[4]->setMode(FMOD_3D);
		mFmodSystem->playSound(mFmodSound[4], NULL, false, &mFmodChannel[4]);
		break;
	}
	case 5: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		/*result = loadSoundFile(SOUND_FILE_PATH[5], soundNum);
		if (result != FMOD_OK)
			return;*/
		//mFmodSound[5]->setMode(FMOD_3D);
		mFmodSystem->playSound(mFmodSound[5], NULL, false, &mFmodChannel[5]);
		break;
	}
	case 6: {
		result = mFmodChannel[soundNum]->isPlaying(&isPlaying);
		if (result == FMOD_OK)
			return;

		/*result = loadSoundFile(SOUND_FILE_PATH[6], soundNum);
		if (result != FMOD_OK)
			return;*/
		//mFmodSound[6]->setMode(FMOD_3D);
		mFmodSystem->playSound(mFmodSound[6], NULL, false, &mFmodChannel[6]);
		break;
	}
	default:break;
	}
}

void SoundManager::playOverlapSound(FMOD::Channel*& channel, int soundNum)
{
	//bool isPlaying = false;
	//FMOD_RESULT result;
	//result = channel->isPlaying(&isPlaying);
	//if (result == FMOD_OK)
	//	return;
	//result = loadSoundFile(SOUND_FILE_PATH[soundNum], soundNum);
	//if (result != FMOD_OK)
	//	return;
	mFmodSystem->playSound(mFmodSound[soundNum], NULL, false, &channel);
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
	//FMOD_VECTOR points[3] = {
	//{1.f,1.f,0.f},
	//{20.f,0.5f,0.f},
	//{100.f,0.f,0.f}
	//};
	FMOD_RESULT result = FMOD_OK;
	for (int i = 0; i < SOUND_NUM; i++) {
		const char* soundfilename = SOUND_FILE_PATH[i].c_str();
		result = mFmodSystem->createSound(soundfilename, FMOD_3D, NULL, &mFmodSound[i]);
		if (result != FMOD_OK) return result;
		if (i == 0) mFmodSound[0]->setMode(FMOD_LOOP_NORMAL);
		mFmodSound[i]->set3DMinMaxDistance(10.f, 1000.f);
		/*mFmodSound[i]->setMode(FMOD_3D_CUSTOMROLLOFF);
		mFmodSound[i]->set3DCustomRolloff(points, 3);*/
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
