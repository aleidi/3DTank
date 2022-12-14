#pragma once
#include "GameCommon.h"
#include "UIButton.h"

class UIText;
class UIEvent;

class GameButton : public GameObject
{
public:
	GameButton(const std::wstring& texPath, float width, float height, const std::wstring& text);
	~GameButton();

	void setPosition(float x, float y);
	void setEnable(bool value);
	void setButtonPos(float x, float y);
	void setTextPos(float x, float y);
	void setButtonColor(XMFLOAT4 color, UIButton::State btnState);
	void setButtonSize(float x, float y);
	void setBtnEvent(UIEvent* event);
	void setText(const std::wstring& text);

private:
	UIText* mText;
	UIButton* mButton;

	float mWidth;
	float mHeight;
};

