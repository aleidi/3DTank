#include "Engine.h"
#include "Graphics.h"
#include "Window.h"
#include "TestCube.h"
#include "Sound.h"
#include <sstream>

//test code
std::vector<std::unique_ptr<TestCube>> cubes;

Engine::Engine(Window& wnd)
	:
	mWnd(wnd),
	mGraphics(new Graphics(wnd)),
	mSound(new Sound())
{
	//test code
	//set cubes
	cubes.push_back(std::make_unique<TestCube>(*mGraphics));

	mGraphics->SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));


}

void Engine::OnInit()
{
	//Timer Init
	mTimer.reset();

	float fScale = 1.0f;
	float fTrans_x = 0.0f;
	float fTrans_y = 0.0f;
	float fTrans_z = 1.0f;

	//Input Init
	DInputPC::getInstance().initialize(mWnd.getHwnd(), mWnd.getHinst(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	//Sound Init
	mSound->initialize();

	//SceneManagerInit

	//Gui Init

	//EUI Init
}

void Engine::run()
{
	//Timer update
	mTimer.tick();

	//Input Update

	//Sound Update
	mSound->playBGM();

	// physics.Update()

	// input.update();
	// input test code
	DInputPC::getInstance().getInput();

	// if (DInputPC::getInstance().iskeyDown(DIK_A)) MessageBox(mWnd.getHwnd(), L"I pressed A", L"Input_Test", MB_OK);

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
			
			////////////////Rotate///////////////////
			if (DInputPC::getInstance().isMouseButtonDown(0)) {
				c->Rotate(DInputPC::getInstance().mouseDY()*mTimer.getDeltaTIme() * 50, DInputPC::getInstance().mouseDX()*mTimer.getDeltaTIme() * 50,
					DInputPC::getInstance().mouseDZ()*mTimer.getDeltaTIme() * 50);
			}
			 
			///////////////Translate//////////////////
			if (DInputPC::getInstance().iskeyDown(DIK_A)) fTrans_x = -0.05f;
			else if (DInputPC::getInstance().iskeyDown(DIK_D)) fTrans_x = 0.05f;
			else fTrans_x = 0.0f;
			if (DInputPC::getInstance().iskeyDown(DIK_SPACE)) fTrans_y = 0.05f;
			else if (DInputPC::getInstance().iskeyDown(DIK_LCONTROL)) fTrans_y = -0.05f;
			else fTrans_y = 0.0f;
			if (DInputPC::getInstance().iskeyDown(DIK_W)) fTrans_z = 0.05f;
			else if (DInputPC::getInstance().iskeyDown(DIK_S)) fTrans_z = -0.05f;
			else fTrans_z = 0.0f;
			c->Translate(fTrans_x, fTrans_y, fTrans_z);
			
			/////////////////Scale////////////////////
			if (DInputPC::getInstance().isMouseButtonDown(1)) {
				if (DInputPC::getInstance().mouseDZ() > 0) {
					fScale += 0.05f ;
					c->Scale(fScale, fScale, fScale);
				}
				else if(DInputPC::getInstance().mouseDZ() < 0) {
					fScale -= 0.05f ;
					c->Scale(fScale, fScale, fScale);
				}
			}
			
			/*
			if (DInputPC::getInstance().isMouseButtonDown(1)) {
				std::wostringstream outss;
				outss.precision(6);
				if (DInputPC::getInstance().mouseDZ() != 0) {
					i = i*DInputPC::getInstance().mouseDZ()*0.01;
					i++;
					outss << WNDTITLE << "i:" << i;
					MessageBoxW(mWnd.getHwnd(), outss.str().c_str(), L"Input_Test", MB_OK);
				}
			} */
			
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
		outs << WNDTITLE << "   " << "FPS: " << fps << "   " << "Frame Time: " << mspf << "(ms)" ;
		SetWindowText(mWnd.getHwnd(), outs.str().c_str());

		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}