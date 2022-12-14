#pragma once
#include <string>
#include "fmod/fmod.hpp"
#include "fmod/fmod.h"
#include "Vector3.h"

#pragma comment (lib,"fmod_vc.lib")
#pragma comment (lib,"fmodL_vc.lib")


const int SOUND_NUM_01 = 7;
const std::string SOUND_FILE_PATH_01[7] =
{
	"Resource/Sound/BGM00_Background.wav",
	"Resource/Sound/BGM01_Button_click.wav",
	"Resource/Sound/SE00_Tank_move_lp.wav",
	"Resource/Sound/SE01_Tank_shot.wav",
	"Resource/Sound/SE02_Tank_explossion.wav",
	"Resource/Sound/SE03_Shell_flyby.wav",
	"Resource/Sound/SE04_Shell_boom.wav"
};

//enum MusicIndex { BGM, BUTTON_CLICK, TNAK_MOVE, TANK_SHOT, TANK_EXPLOSSION, SHELL_FLYBY, SHELL_BOOM };

class Sound
{
public:
	

	Sound();
	Sound(const Sound&);
	~Sound();
public:
	bool onInit();
	void playBGM();
	void play(const int&, const Vector3*);
	bool setPause(const int&);
	bool setReplay(const int&);
	bool stop(const int&);
	void onUpdate(const float&);
	void shutDown();
	void setPosition();
	//void setPosition(const Vector3&);

	FMOD_RESULT loadSoundFile(std::string filename, int soundidx);
private:
	FMOD::System *mFmodAudio;
	FMOD::Sound *mFmodSound[SOUND_NUM_01];
	FMOD::Channel *mFmodChannel[SOUND_NUM_01];

};