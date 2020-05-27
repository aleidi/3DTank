#include "Engine.h"
#include "Graphics.h"
#include "Window.h"
#include "Box.h"
#include "TestCube.h"
#include<sstream>

//test code
std::vector<std::unique_ptr<Box>> boxes;
std::vector<std::unique_ptr<TestCube>> cubes;

Engine::Engine(Window& wnd)
	:
	mWnd(wnd),
	mGraphics(new Graphics(wnd))
{
	mTimer.reset();

	//test code
	////set boxes
	//std::mt19937 rng(std::random_device{}());
	//std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	//std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	//std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	//std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	//for (auto i = 0; i < 80; i++)
	//{
	//	boxes.push_back(std::make_unique<Box>(
	//		*mGraphics, rng, adist,
	//		ddist, odist, rdist
	//		));
	//}

	//set cubes
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 80; i++)
	{
		cubes.push_back(std::make_unique<TestCube>(
			*mGraphics, rng, adist,
			ddist, odist, rdist
			));
	}

	mGraphics->SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

void Engine::run()
{
	//timer update
	mTimer.tick();

	{
		//test code
		calculateFrameStats();
		//render update
		mGraphics->CleanFrame();
		//for (auto& b : boxes)
		//{
		//	b->Update(mTimer.getDeltaTIme());
		//	b->Draw(*mGraphics);
		//}
		for (auto& c : cubes)
		{
			c->Update(mTimer.getDeltaTIme());
			c->Draw(*mGraphics);
		}
	}
	mGraphics->EndFrame();
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