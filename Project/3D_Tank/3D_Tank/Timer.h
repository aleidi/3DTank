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
	__int64 m_baseTime;
	__int64 m_pausedTime;
	__int64 m_stopTime;
	__int64 m_prevTime;
	__int64 m_currTime;

	double m_secondsPerCount;
	double m_deltaTime;

	bool m_stopped;
};

