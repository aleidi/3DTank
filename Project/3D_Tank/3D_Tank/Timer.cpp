#include "Timer.h"

Timer::Timer()
	:
	mBaseTime(0),mPausedTime(0),mStopTime(0),
	mPrevTime(0),m_currTime(0),
	mSecondsPerCount(0.0),mDeltaTime(-1.0),
	mStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);

	mSecondsPerCount = 1.0 / (double)countsPerSec;

}

Timer::~Timer()
{

}

float Timer::getTotalTime() const
{
	if (mStopped)
	{
		return (float)((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount;
	}
	else
	{
		return (float)((m_currTime - mPausedTime) - mBaseTime) * mSecondsPerCount;
	}
}

float Timer::getDeltaTIme() const
{
	return (float)mDeltaTime;
}

void Timer::reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void Timer::start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (mStopped)
	{
		mPausedTime += startTime - mStopTime;
		mPrevTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void Timer::stop()
{
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		mStopTime = currTime;
		mStopped = true;
	}
}

void Timer::tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_currTime = currTime;

	//计算当前帧和上一帧的时间差
	mDeltaTime = (m_currTime - mPrevTime) * mSecondsPerCount;

	//为下一帧做准备
	mPrevTime = m_currTime;

	//DXSDK的CDXUTTimer提到：如果处理器进入节电模式或切换至另一个处理器，mDeltaTime会变成负值
	//要确保mDeltaTime不为负值
	if (mDeltaTime < 0)
	{
		mDeltaTime = 0;
	}
}
