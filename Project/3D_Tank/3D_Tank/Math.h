#pragma once
#include "EngineCommon.h"
#include <math.h>

const float Pi = 3.1415926f;

class Math
{
public:
	static Vector3 lerp(const Vector3& src, const Vector3& dst, float t)
	{
		return src * (1 - t) + dst * t;
	}

	static float lerp(float src, float dst, float t)
	{
		return src * (1 - t) + dst * t;
	}

	template <class T>
	static inline T MaxOf(const T& a, const T& b)
	{
		if (a > b) return a; return b;
	}

	//returns the minimum of two values
	template <class T>
	static inline T MinOf(const T& a, const T& b)
	{
		if (a < b) return a; return b;
	}

	static inline float RandFloat() {
		return (float)(rand() / (RAND_MAX + 1.0f));
	}

	static inline float RandomClamped() { return RandFloat() - RandFloat(); }


	static inline float Clamp(float max, float min, float& num) {
		if (num > max) num = max;
		if (num < min) num = min;
		return num;
	}

};