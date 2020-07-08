#pragma once
#include "Track.h"
#include "Vector3.h"

class Transform;

namespace Sequence
{
	struct Transform
	{
		Vector3 Position;
		Vector3 Rotation;
		Vector3 Scale;
	};
}

class TrackTransform : public Track<Sequence::Transform>
{
	using Track<Sequence::Transform>::mKeyFrames;
public:
	TrackTransform(Transform* target);
	~TrackTransform();

	void play(const float& deltaTime) override;

private:
	Transform* mTarget;
};

