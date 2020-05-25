#include "Timer.h"

Timer::Timer()
	:
	m_baseTime(0),m_pausedTime(0),m_stopTime(0),
	m_prevTime(0),m_currTime(0),
	m_secondsPerCount(0.0),m_deltaTime(-1.0),
	m_stopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);

	m_secondsPerCount = 1.0 / (double)countsPerSec;

}

Timer::~Timer()
{

}

float Timer::getTotalTime() const
{
	if (m_stopped)
	{
		return (float)((m_stopTime - m_pausedTime) - m_baseTime) * m_secondsPerCount;
	}
	else
	{
		return (float)((m_currTime - m_pausedTime) - m_baseTime) * m_secondsPerCount;
	}
}

float Timer::getDeltaTIme() const
{
	return (float)m_deltaTime;
}

void Timer::reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_baseTime = currTime;
	m_prevTime = currTime;
	m_stopTime = 0;
	m_stopped = false;
}

void Timer::start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (m_stopped)
	{
		m_pausedTime += startTime - m_stopTime;
		m_prevTime = startTime;
		m_stopTime = 0;
		m_stopped = false;
	}
}

void Timer::stop()
{
	if (!m_stopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_stopTime = currTime;
		m_stopped = true;
	}
}

void Timer::tick()
{
	if (m_stopped)
	{
		m_deltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_currTime = currTime;

	//计算当前帧和上一帧的时间差
	m_deltaTime = (m_currTime - m_prevTime) * m_secondsPerCount;

	//为下一帧做准备
	m_prevTime = m_currTime;

	//DXSDK的CDXUTTimer提到：如果处理器进入节电模式或切换至另一个处理器，m_deltaTime会变成负值
	//要确保m_deltaTime不为负值
	if (m_deltaTime < 0)
	{
		m_deltaTime = 0;
	}
}
