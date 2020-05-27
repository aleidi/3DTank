#include "Engine.h"
#include "Graphics.h"
#include "Window.h"
#include "Box.h"
#include "TestCube.h"
#include "Sound.h"
#include <sstream>

//test code
std::vector<std::unique_ptr<TestCube>> cubes;

Engine::Engine(Window& wnd)
	:
	mWnd(wnd),
	mGraphics(new Graphics(wnd))
{
	mTimer.reset();

	//test code
	//set cubes
	cubes.push_back(std::make_unique<TestCube>(*mGraphics));

	mGraphics->SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));

	mDInput = new DInputPC();
	mDInput->initialize(mWnd.getHwnd(), mWnd.getHinst(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

void Engine::run()
{
	//timer update
	mTimer.tick();
	// physics.Update()
	// input.update();
	// input test code
	mDInput->getInput();
	if (mDInput->iskeyDown(DIK_A)) MessageBox(mWnd.getHwnd(), L"I pressed A", L"Input_Test", MB_OK);

	/*
	render.update();
	gameUI.Update();
	eui.update();
	*/

	{
		//test code
		calculateFrameStats();
		//render.update()
		mGraphics->CleanFrame();
		for (auto& c : cubes)
		{
			c->Update(mTimer.getDeltaTIme());
			c->Draw(*mGraphics);
		}
	}
	mGraphics->EndFrame();

	Sound *mSound = new Sound;
	mSound->initialize();
	mSound->playBGM();
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