#include "Engine.h"
#include "Window.h"
#include "TestCube.h"
#include "ModelMesh.h"
#include <sstream>

//test code
std::vector<std::unique_ptr<TestCube>> cubes;
std::vector<std::unique_ptr<ModelMesh>> tanks;

static float dis = 0.0f;
Engine* Engine::sInstance = nullptr;

Engine::Engine(Window& wnd)
	:
	mWnd(wnd),
	mSound(std::make_unique<Sound>()),
	mRendering(std::make_unique<Rendering>(wnd))
{

}

Engine * Engine::sGetInstance()
{
	return sInstance;
}

void Engine::createSingleton(Window & wnd)
{
	assert(!sInstance);
	sInstance = new Engine(wnd);
}

void Engine::Destroy()
{
	delete sInstance;
	sInstance = nullptr;
}

void Engine::onInit()
{
	//Timer Init
	mTimer.reset();

	//test code
	calculateFrameStats();

	 fScale = 1.0f;
	 fTrans_x = 0.0f;
	 fTrans_y = 0.0f;
	 fTrans_z = 0.0f;
	 fRot_x = 0.0f;
	 fRot_y = 0.0f;
	 fRot_z = 0.0f;

	//Input Init
	DInputPC::getInstance().onInit(mWnd.getHwnd(), mWnd.getHinst(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	//Sound Init
	mSound->onInit();
	mSound->playBGM();

	//Rendering Init
	mRendering.get()->onInit();

	//SceneManagerInit

	//Gui Init

	//EUI Init

	//test code
	//set cubes
	cubes.push_back(std::make_unique<TestCube>(*mRendering.get()->getGFX()));
	tanks.push_back(std::make_unique<ModelMesh>(*mRendering.get()->getGFX()));
}

void Engine::run()
{
	//Timer update
	mTimer.tick();
	calculateFrameStats();

	//Input Update
	DInputPC::getInstance().onUpdate();

	//Physics Update

	//Game Update
	
	//Sound Update
	dis += fTrans_z;
	mSound->onUpdate(dis);

	//PreRender
	mRendering.get()->onPreRender(mTimer.getDeltaTIme());

	//OnRender
	mRendering.get()->onRender(mTimer.getDeltaTIme());

#pragma region test code

	if (DInputPC::getInstance().iskey(DIK_W))
	{
		fTrans_z += mTimer.getDeltaTIme();
	}
	if (DInputPC::getInstance().iskey(DIK_S))
	{
		fTrans_z -= mTimer.getDeltaTIme();
	}
	if (DInputPC::getInstance().iskey(DIK_A))
	{
		fTrans_x -= mTimer.getDeltaTIme();
	}
	if (DInputPC::getInstance().iskey(DIK_D))
	{
		fTrans_x += mTimer.getDeltaTIme();
	}
	if (DInputPC::getInstance().iskey(DIK_Q))
	{
		fTrans_y += mTimer.getDeltaTIme();
	}
	if (DInputPC::getInstance().iskey(DIK_E))
	{
		fTrans_y -= mTimer.getDeltaTIme();
	}
	if (DInputPC::getInstance().iskey(DIK_I))
	{
		fRot_x -= mTimer.getDeltaTIme();
	}
	if (DInputPC::getInstance().iskey(DIK_K))
	{
		fRot_x += mTimer.getDeltaTIme();
	}
	if (DInputPC::getInstance().iskey(DIK_J))
	{
		fRot_y -= mTimer.getDeltaTIme();
	}
	if (DInputPC::getInstance().iskey(DIK_L))
	{
		fRot_y += mTimer.getDeltaTIme();
	}
	if (DInputPC::getInstance().iskey(DIK_U))
	{
		fRot_z -= mTimer.getDeltaTIme();
	}
	if (DInputPC::getInstance().iskey(DIK_O))
	{
		fRot_z += mTimer.getDeltaTIme();
	}
	mRendering.get()->getGFX()->CamSetPosition(fTrans_x, fTrans_y, fTrans_z);
	mRendering.get()->getGFX()->CamSetRotation(fRot_x, fRot_y, fRot_z);


	if (DInputPC::getInstance().iskeyDown(DIK_1))
	{
		showtText(L"FUCK!!!", 0, 0, 200, 200, true);
	}
	if (DInputPC::getInstance().iskeyDown(DIK_2))
	{
		showtText(L"FUCKFUCK!!!!!!", 0, 0, 400, 400, true);
	}
	if (DInputPC::getInstance().iskeyDown(DIK_0))
	{
		showtText(L"", 0, 0, 0, 0, false);
	}


	//for (auto& c : cubes)
	//{
	//	c->Update(mTimer.getDeltaTIme());

	//	c->Draw(*mRendering.get()->getGFX());
	//}

	for (auto& t : tanks)
	{
		t->Update(mTimer.getDeltaTIme());

		t->Draw(*mRendering.get()->getGFX());
	}
#pragma endregion


	//PostRender
	mRendering.get()->onPostRender(mTimer.getDeltaTIme());

	/*
	gameUI.Update();
	eui.update();
	*/


}

void Engine::showtText(const std::wstring & str = L"", float leftTopX=0, float leftTopY=0, float width=0, float height=0, bool canShow = false)
{
	mRendering->getGFX()->setShowText(str, leftTopX, leftTopY, width, height, canShow);
}

void Engine::calculateFrameStats()
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	++frameCnt;

	if ((mTimer.getTotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt;
		float mspf = 1000 / fps;

		std::wostringstream outs;
		outs.precision(6);
		outs << WNDTITLE << "   " << "FPS: " << fps << "   " << "Frame Time: " << mspf << "(ms)";
		SetWindowText(mWnd.getHwnd(), outs.str().c_str());
		
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}