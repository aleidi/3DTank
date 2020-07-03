#pragma once
#include "GameObject.h"
#include "UICommon.h"

class UIImage3D;

class UIHP : public GameObject
{
public:
	UIHP();
	~UIHP();

	void onLateUpdate(float deltaTime) override;

	void setFillAmount(float value);
	void setFillType(FillType type);
	void setEnable(bool value);
	void setFrameSize(float x, float y);
	void setImageSize(float x, float y);

private:
	UIImage3D* mImage;
	UIImage3D* mFrame;
};

