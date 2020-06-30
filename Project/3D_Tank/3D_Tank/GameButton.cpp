#include "GameButton.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "UIText.h"

GameButton::GameButton(const std::wstring & texPath, float width, float height, const std::wstring& text)
	:mWidth(width),mHeight(height)
{
	Graphics& gfx = RenderManager::sGetInstance()->getGraphics();
	mButton = SceneManager::sGetInstance()->createUIButton(texPath);
	mButton->setSize(width, height);
	mText = SceneManager::sGetInstance()->createUIText(text);
}

GameButton::~GameButton()
{
	delete mButton;
	mButton = nullptr;
	delete mText;
	mText = nullptr;
}

void GameButton::setEnable(bool value)
{
	mButton->setEnable(value);
	mText->setEnable(value);
}

void GameButton::setButtonPos(float x, float y)
{
	mButton->setPosition(x, y);
}

void GameButton::setTextPos(float x, float y)
{
	mText->setPosition(x, y);
}

void GameButton::setButtonColor(XMFLOAT4 color, UIButton::State btnState)
{
	mButton->setColor(color, btnState);
}

void GameButton::setButtonSize(float x, float y)
{
	mButton->setSize(x, y);
}

void GameButton::setBtnEvent(UIEvent * event)
{
	mButton->setEvent(event);
}

void GameButton::setText(const std::wstring & text)
{
	mText->setText(text);
}

void GameButton::setPosition(float x, float y)
{
	mButton->setPosition(x, y);
	mText->setPosition(x, y + mHeight / 2);
}
