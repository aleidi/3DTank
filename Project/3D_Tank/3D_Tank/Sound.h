#pragma once
#include <string>
#include "fmod/fmod.hpp"
#include "fmod/fmod.h"

#pragma comment (lib,"fmod_vc.lib")
#pragma comment (lib,"fmodL_vc.lib")


const int SOUND_NUM = 7;
const std::string SOUND_FILE_PATH[7] =
{
	"../Resource/Sound/Music.wav",
	"../Resource/Sound/Tank_move_lp.wav",
	"../Resource/Sound/Tank_Shot.wav",
	"../Resource/Sound/Shell_Flyby.wav",
	"../Resource/Sound/Boom.wav",
	"../Resource/Sound/Button_Click.wav",
	"../Resource/Sound/Explossion.wav"
};

class Sound
{
public:
	Sound();
	Sound(const Sound&);
	~Sound();
public:
	bool initialize();
	void playBGM();
	void play(const int&);
	void stop();
	void shutDown();

	FMOD_RESULT loadSoundFile(std::string filename, int soundidx);
private:
	FMOD::System *mAudio;
	FMOD::Sound *mSound[7];
	FMOD::Channel *mChannel;
	
};