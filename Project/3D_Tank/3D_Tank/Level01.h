#pragma once

#include "GameCommon.h"
#include "GameLevelBase.h"
#include "ULevelEvent.h"

class GameButton;
class AnimationTitle;
class ParticleSystem;
class FadeInOut;

class Level01 : public GameLevelBase
{
public:
	enum State
	{
		Empty,
		MainMenu,
		GameMode,
		Setting,
		Exit,
		GameStart,
		EditStart,
		CompanyTitle,
		TeamTitle,
		Canvas,
		LoadingGame,
		LoadingEdit,
	};

public :
	Level01();
	~Level01();

	void enterLevel() override;
	GameLevelBase* onUpdate(float deltaTime) override;
	void leaveLevel() override;
	void changeState(State s);
	void changeLanguage();
	void loadResourcce() override;

private:
	void loadParticle();

private:
	State mState;

	GameButton* mBtnStart;
	GameButton* mBtnSetting;
	GameButton* mBtnExit;
	GameButton* mBtnGameMode;
	GameButton* mBtnEditMode;
	GameButton* mBtnCN;
	GameButton* mBtnEN;
	GameButton* mBtnShutDown;
	GameButton* mBtnReturn;
	GameButton* mBtnCancel;

	UStartEvent* mStartEvent;
	USetEvent* mSettingEvent;
	UExitEvent* mExitEvent;
	UGmeModeEvent* mGameModeEvent;
	UEditModeEvent* mEditEvent;
	UCNEvent* mCNEvent;
	UENEvent* mENEvent;
	UShutDownEvent* mShutDownEvent;
	UReturnEvent* mReturnEvent;
	UCancelEvent* mCancelEvent;

	AnimationTitle* mCompanyTitle;
	AnimationTitle* mTeamTitle;
	AnimationTitle* mCanvas;

	GameObject* mExhibition;
	GameObject* mCamFollower;
	GameObject* mCamera;

	ParticleSystem* mRain;
	bool mCamTrig;

	FadeInOut* mFadeInImage;
};

