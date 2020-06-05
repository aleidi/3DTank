#include "EngineCommon.h"

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
};