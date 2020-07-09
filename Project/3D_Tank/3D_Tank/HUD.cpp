#include "HUD.h"
#include "GameCommon.h"
#include "UIBase.h"
#include "UIImage.h"

HUD::HUD()
	:mRotSpdInner(0.2f), mRotSpdOuter(0.35f),
	mAccelatorInner(1.0f),mAccelatorOuter(1.0f)

{
	mName = "HUD";
	float width = 300.0f;
	float height = 300.0f;
	float posw = WINDOW_WIDTH * 0.5f - width * 0.5f;
	float posh = WINDOW_HEIGHT * 0.5f - height * 0.5f;
	mCrossHairInner = SceneManager::sGetInstance()->createUIImage(L"UI/crosshair_inner");
	mCrossHairInner->setBlend(true);
	mCrossHairInner->setSize(width, height);
	mCrossHairInner->setPosition(posw, posh);
	mCrossHairInner->setEnable(false);
	mCrossHairOuter = SceneManager::sGetInstance()->createUIImage(L"UI/crosshair_mid");
	mCrossHairOuter->setSize(width, height);
	mCrossHairOuter->setPosition(posw, posh);
	mCrossHairOuter->setBlend(true);
	mCrossHairOuter->setEnable(false);
}

HUD::~HUD()
{
	SceneManager::sGetInstance()->removreUIFromPool(dynamic_cast<UIBase*>(mCrossHairInner));
	SceneManager::sGetInstance()->removreUIFromPool(dynamic_cast<UIBase*>(mCrossHairOuter));
}

void HUD::setAccelator(const float& inner, const float& outer)
{
	mAccelatorInner = inner;
	mAccelatorOuter = outer;
}

void HUD::onLateUpdate(const float& deltaTime)
{
	mCrossHairInner->rotate(0.0f, 0.0f, deltaTime * mRotSpdInner * mAccelatorInner);
	mCrossHairOuter->rotate(0.0f, 0.0f, deltaTime * mRotSpdOuter * mAccelatorOuter * -1.0f);
}

void HUD::enableShow(const bool& value)
{
	mCrossHairInner->setEnable(value);
	mCrossHairOuter->setEnable(value);
}
