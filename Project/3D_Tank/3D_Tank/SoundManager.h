#pragma once
#include <string>
#include "fmod/fmod.hpp"
#include "fmod/fmod.h"
#include "Vector3.h"

#pragma comment (lib,"fmod_vc.lib")
#pragma comment (lib,"fmodL_vc.lib")

const int SOUND_NUM = 7;

const std::string SOUND_FILE_PATH[7] =
{
	"Resource/Sound/BGM00_Background.wav",
	"Resource/Sound/BGM01_Button_click.wav",
	"Resource/Sound/SE00_Tank_move_lp.wav",
	"Resource/Sound/SE01_Tank_shot.wav",
	"Resource/Sound/SE02_Tank_explossion.wav",
	"Resource/Sound/SE03_Shell_flyby.wav",
	"Resource/Sound/SE04_Shell_boom.wav"
};

enum MusicManagerIndex { BGM, BUTTON_CLICK, TNAK_MOVE, TANK_SHOT, TANK_EXPLOSSION, SHELL_FLYBY, SHELL_BOOM };

class SoundManager
{
public:
	static SoundManager* sGetInstance();
	static void onInit();

	void playBGM();
	void playSound(const int& soundNum);
	void playSound(FMOD::Channel*& channel, int soundNum);
	void setPause(const int& soundNum);
	void setReplay(const int& soundNum);
	void stop(const int& soundNum);
	void onUpdate();
	void setSoundPosAndVel(const Vector3& pos, const Vector3& vel, const int& soundNum);
	void setLisenterPosition(const Vector3& pos);
	FMOD_RESULT loadSoundFile(const std::string& filepath, const int& soundNum);
	FMOD_RESULT loadALLSoundFile();
	//FMOD_RESULT loadSoundFile(const std::string& filepath, const int& soundNum);

private:
	static SoundManager* sInstance;
	SoundManager();
	~SoundManager();
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;


private:
	FMOD::System* mFmodSystem;
	FMOD::Sound* mFmodSound[SOUND_NUM];
	FMOD::Channel* mFmodChannel[SOUND_NUM];
};