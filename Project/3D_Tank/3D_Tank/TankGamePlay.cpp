#include "TankGamePlay.h"
#include "GameCommon.h"
#include "Transform.h"

TankGamePlay::TankGamePlay(GameObject * object) noexcept
	:ScriptComponent(object)
{
}

void TankGamePlay::onUpdate(float deltaTime)
{
	if (DInputPC::getInstance().iskey(DIK_NUMPAD8))
	{
		mTransform->translate(mTransform->Forward*deltaTime*3.0f);
	}
	if (DInputPC::getInstance().iskey(DIK_NUMPAD5))
	{
		mTransform->translate(mTransform->Forward*deltaTime*(-3.0f));
	}
	if (DInputPC::getInstance().iskey(DIK_NUMPAD6))
	{
		mTransform->rotateY(deltaTime*8.0f);
	}
	if (DInputPC::getInstance().iskey(DIK_NUMPAD4))
	{
		mTransform->rotateY(deltaTime*(-8.0f));
	}

	std::wstring wc = L"ForwardX: ";
	wc += std::to_wstring(mTransform->Forward.x);
	wc += L", ForwardY: ";
	wc += std::to_wstring(mTransform->Forward.y);
	wc += L", ForwardZ: ";
	wc += std::to_wstring(mTransform->Forward.z);

	Engine::sGetInstance()->showtText(wc.c_str(), 0, 0, 600, 600, true);
}
