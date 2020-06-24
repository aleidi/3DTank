#pragma once
#include "GameObject.h"

class UIImage3D;

class UIHP : public GameObject
{
public:
	UIHP();
	~UIHP();

	void onLateUpdate(float deltaTime) override;

private:
	UIImage3D* mImage;
};

