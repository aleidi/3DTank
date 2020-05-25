#include "Timer.h"

Timer::Timer()
	:
	mBaseTime(0),mPausedTime(0),mStopTime(0),
	mPrevTime(0),mCurrTime(0),
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
		return (float)((mCurrTime - mPausedTime) - mBaseTime) * mSecondsPerCount;
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
	mCurrTime = currTime;

	//���㵱ǰ֡����һ֡��ʱ���
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

	//Ϊ��һ֡��׼��
	mPrevTime = mCurrTime;

	//DXSDK��CDXUTTimer�ᵽ���������������ڵ�ģʽ���л�����һ����������mDeltaTime���ɸ�ֵ
	//Ҫȷ��mDeltaTime��Ϊ��ֵ
	if (mDeltaTime < 0)
	{
		mDeltaTime = 0;
	}
}
