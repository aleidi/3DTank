#pragma once
#include <vector>

template<typename T>
class Track
{
public:
	struct Frame
	{
		float Key;
		T KeyData;
	};
public:
	Track() = default;
	virtual ~Track() = default;

	virtual void play(const float& deltaTime) = 0;
	void addKeyFrame(Frame keyFrame)
	{
		mKeyFrames.push_back(keyFrame);
	}

protected:
	std::vector<Frame> mKeyFrames;
	int mCurrentKey;
	float mCurrentTime;
	bool mIsActivate;
};
