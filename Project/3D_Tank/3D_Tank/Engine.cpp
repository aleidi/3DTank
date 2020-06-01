#include "Engine.h"
#include "Window.h"
#include "TestCube.h"
#include <sstream>

//test code
std::vector<std::unique_ptr<TestCube>> cubes;
static float dis = 0.0f;

Engine::Engine(Window& wnd)
	:
	mWnd(wnd),
	mSound(std::make_unique<Sound>()),
	mRendering(std::make_unique<Rendering>(wnd))
{

}

void Engine::OnInit()
{
	//Timer Init
	mTimer.reset();

	//test code
	calculateFrameStats();

	float fScale = 1.0f;
	float fTrans_x = 0.0f;
	float fTrans_y = 0.0f;
	float fTrans_z = 0.0f;

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
		fTrans_z -= mTimer.getDeltaTIme();
		mRendering.get()->getGFX()->CamSetRotation(fTrans_x, fTrans_y, fTrans_z);
	}
	if (DInputPC::getInstance().iskey(DIK_S))
	{
		fTrans_z += mTimer.getDeltaTIme();
		mRendering.get()->getGFX()->CamSetRotation(fTrans_x, fTrans_y, fTrans_z);
	}
	if (DInputPC::getInstance().iskey(DIK_A))
	{
		fTrans_x -= mTimer.getDeltaTIme();
		mRendering.get()->getGFX()->CamSetRotation(fTrans_x, fTrans_y, fTrans_z);
	}
	if (DInputPC::getInstance().iskey(DIK_D))
	{
		fTrans_x += mTimer.getDeltaTIme();
		mRendering.get()->getGFX()->CamSetRotation(fTrans_x, fTrans_y, fTrans_z);
	}


	for (auto& c : cubes)
	{
		c->Update(mTimer.getDeltaTIme());

		c->Draw(*mRendering.get()->getGFX());
	}
#pragma endregion


	//PostRender
	mRendering.get()->onPostRender(mTimer.getDeltaTIme());

	/*
	gameUI.Update();
	eui.update();
	*/


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