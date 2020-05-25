#pragma once
#include <windows.h>

class Timer
{
public:
	Timer();
	~Timer();

	float getTotalTime() const;
	float getDeltaTIme() const;

	void reset();
	void start();
	void stop();
	void tick();
private:
	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	double mSecondsPerCount;
	double mDeltaTime;

	bool mStopped;
};

