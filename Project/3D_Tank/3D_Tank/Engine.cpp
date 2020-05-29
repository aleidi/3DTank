#include "Engine.h"
#include "Graphics.h"
#include "Window.h"
#include "TestCube.h"
#include "Sound.h"
#include <sstream>

//test code
std::vector<std::unique_ptr<TestCube>> cubes;
static float dis = 0.0f;

Engine::Engine(Window& wnd)
	:
	mWnd(wnd),
	mGraphics(new Graphics(wnd)),
	mSound(new Sound())
{
	//test code
	//set cubes
	cubes.push_back(std::make_unique<TestCube>(*mGraphics));
}

void Engine::OnInit()
{
	//Timer Init
	mTimer.reset();

	float fScale = 1.0f;
	float fTrans_x = 0.0f;
	float fTrans_y = 0.0f;
	float fTrans_z = 0.0f;

	//Input Init
	DInputPC::getInstance().onInit(mWnd.getHwnd(), mWnd.getHinst(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	//Sound Init
	mSound->onInit();
	mSound->playBGM();

	//SceneManagerInit

	//Gui Init

	//EUI Init
}

void Engine::run()
{
	//Timer update
	mTimer.tick();

	//Input Update
	DInputPC::getInstance().onUpdate();
	
	//Sound Update
	dis += fTrans_z;
	mSound->onUpdate(dis);

	// physics.Update()

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
			/*
			if (DInputPC::getInstance().isMouseButton(0)) {
				c->Rotate(DInputPC::getInstance().mouseDY()*mTimer.getDeltaTIme() * 50, DInputPC::getInstance().mouseDX()*mTimer.getDeltaTIme() * 50,
					DInputPC::getInstance().mouseDZ()*mTimer.getDeltaTIme() * 50);
			}
			*/
			/////////////////Translate//////////////////
			//if (DInputPC::getInstance().isMouseButtonDown(0)) fTrans_y = 5.0f;
			//else if (DInputPC::getInstance().isMouseButtonUp(1)) fTrans_y = -5.0f;
			//else fTrans_y = 0.0f;
			//if (DInputPC::getInstance().iskey(DIK_W)) fTrans_z = 0.05f;
			//else if (DInputPC::getInstance().iskey(DIK_S)) fTrans_z = -0.05f;
			//else fTrans_z = 0.0f;
			//if (DInputPC::getInstance().iskeyDown(DIK_A)) fTrans_x = -5.0f;
			//else if (DInputPC::getInstance().iskeyUp(DIK_D)) fTrans_x = 5.0f;
			//else fTrans_x = 0.0f;
			//c->Translate(fTrans_x, fTrans_y, fTrans_z);


			if (DInputPC::getInstance().iskey(DIK_W))
			{
				fTrans_z -= mTimer.getDeltaTIme();
				mGraphics->CamSetRotation(fTrans_x, fTrans_y, fTrans_z);
			}
			if (DInputPC::getInstance().iskey(DIK_S))
			{
				fTrans_z += mTimer.getDeltaTIme();
				mGraphics->CamSetRotation(fTrans_x, fTrans_y, fTrans_z);
			}
			if (DInputPC::getInstance().iskey(DIK_A))
			{
				fTrans_x -= mTimer.getDeltaTIme();
				mGraphics->CamSetRotation(fTrans_x, fTrans_y, fTrans_z);
			}
			if (DInputPC::getInstance().iskey(DIK_D))
			{
				fTrans_x += mTimer.getDeltaTIme();
				mGraphics->CamSetRotation(fTrans_x, fTrans_y, fTrans_z);
			}

			/////////////////Scale////////////////////
			/*
			if (DInputPC::getInstance().isMouseButton(1)) {
				if (DInputPC::getInstance().mouseDZ() > 0) {
					fScale += 0.05f ;
					c->Scale(fScale, fScale, fScale);
				}
				else if(DInputPC::getInstance().mouseDZ() < 0) {
					fScale -= 0.05f ;
					c->Scale(fScale, fScale, fScale);
				}
			}
			*/
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
		outs << WNDTITLE << "   " << "FPS: " << fps << "   " << "Frame Time: " << mspf << "(ms)"
			<< "transx:"<<fTrans_x;
		SetWindowText(mWnd.getHwnd(), outs.str().c_str());

		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}