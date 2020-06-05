#include <sstream>
#include "Engine.h"
#include "Window.h"
#include "SceneManager.h"
#include "ComponentFactory.h"

#include "GameObject.h"
#include "Transform.h"
#include "ModelMesh.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

Engine* Engine::sInstance = nullptr;

//test code
GameObject* hq;
GameObject* tankBattery;
GameObject* tankBody;
GameObject* tankTrackL;
GameObject* tankTrackR;

static float dis = 0.0f;

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

void Engine::onPreInit()
{
	//Timer Init
	mTimer.reset();

	//SceneManagerInit
	SceneManager::createSingleton();

	//Rendering Init
	mRendering.get()->onInit();
}

void Engine::onInit()
{

	//test code
	calculateFrameStats();

	 fScale = 1.0f;
	 fTrans_x = 0.0f;
	 fTrans_y = 0.0f;
	 fTrans_z = 0.0f;
	 fRot_x = 0.0f;
	 fRot_y = 0.0f;
	 fRot_z = 0.0f;
	 fspeed = 300.0f;
	 rspeed = 5.0f;

	//Input Init
	DInputPC::getInstance().onInit(mWnd.getHwnd(), mWnd.getHinst(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	//Sound Init
	mSound->onInit();
	mSound->playBGM();

	//Game Init


	//Gui Init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(mWnd.getHwnd());
	ImGui_ImplDX11_Init(mRendering->getGFX()->GetDevice(), mRendering->getGFX()->GetContext());
	ImGui::StyleColorsDark();

	//EUI Init

	//test code
	hq = SceneManager::sGetInstance()->createEmptyObject();
	hq->setName("tankA");

	tankBattery = SceneManager::sGetInstance()->createEmptyObject();
	SceneManager::sGetInstance()->createModel(*tankBattery, "Tank\\TankBattery", L"Tank\\TankTex");
	tankBattery->attach(*hq);

	GameObject* tankBody = SceneManager::sGetInstance()->createEmptyObject();
	SceneManager::sGetInstance()->createModel(*tankBody, "Tank\\TankBody", L"Tank\\TankTex");
	tankBody->attach(*hq);

	GameObject* tankTrackL = SceneManager::sGetInstance()->createEmptyObject();
	SceneManager::sGetInstance()->createModel(*tankTrackL, "Tank\\TankTrack_L", L"Tank\\TankTrack");
	tankTrackL->attach(*hq);

	GameObject* tankTrackR = SceneManager::sGetInstance()->createEmptyObject();
	SceneManager::sGetInstance()->createModel(*tankTrackR, "Tank\\TankTrack_R", L"Tank\\TankTrack");
	tankTrackR->attach(*hq);

	hq->getTransform()->Scale = Vector3(0.1f, 0.1f, 0.1f);
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
	SceneManager::sGetInstance()->onUpdate(mTimer.getDeltaTIme());

	//Sound Update
	dis += fTrans_z;
	mSound->onUpdate(dis);

	//PreRender
	mRendering.get()->onPreRender(mTimer.getDeltaTIme());

	//OnRender
	mRendering.get()->onRender(mTimer.getDeltaTIme());

#pragma region test code
	float dt = mTimer.getDeltaTIme() * fspeed;
	float dt2 = mTimer.getDeltaTIme() * rspeed;
	XMVECTOR v = mRendering.get()->getGFX()->getCamPos();
	if (DInputPC::getInstance().iskey(DIK_W))
	{
		v = mRendering.get()->getGFX()->getcamForward();
		v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
		v = XMVectorAdd(mRendering.get()->getGFX()->getCamPos(), v);
	}
	if (DInputPC::getInstance().iskey(DIK_S))
	{
		v = mRendering.get()->getGFX()->getcamForward();
		v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
		v = XMVectorSubtract(mRendering.get()->getGFX()->getCamPos(),v);

	}
	if (DInputPC::getInstance().iskey(DIK_A))
	{
		v = mRendering.get()->getGFX()->getcamRight();
		v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
		v = XMVectorSubtract(mRendering.get()->getGFX()->getCamPos(), v);
	}
	if (DInputPC::getInstance().iskey(DIK_D))
	{
		v = mRendering.get()->getGFX()->getcamRight();
		v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
		v = XMVectorAdd(mRendering.get()->getGFX()->getCamPos(), v);
	}
	if (DInputPC::getInstance().iskey(DIK_Q))
	{
		v = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
		v = XMVectorAdd(mRendering.get()->getGFX()->getCamPos(), v);
	}
	if (DInputPC::getInstance().iskey(DIK_E))
	{
		v = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);
		v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
		v = XMVectorAdd(mRendering.get()->getGFX()->getCamPos(), v);
	}
	if (DInputPC::getInstance().iskey(DIK_I))
	{
		fRot_x -= mTimer.getDeltaTIme() * rspeed;
	}
	if (DInputPC::getInstance().iskey(DIK_K))
	{
		fRot_x += mTimer.getDeltaTIme() * rspeed;
	}
	if (DInputPC::getInstance().iskey(DIK_J))
	{
		fRot_y -= mTimer.getDeltaTIme() * rspeed;
	}
	if (DInputPC::getInstance().iskey(DIK_L))
	{
		fRot_y += mTimer.getDeltaTIme() * rspeed;
	}
	if (DInputPC::getInstance().iskey(DIK_U))
	{
		fRot_z -= mTimer.getDeltaTIme() * rspeed;
	}
	if (DInputPC::getInstance().iskey(DIK_O))
	{
		fRot_z += mTimer.getDeltaTIme() * rspeed;
	}
	mRendering.get()->getGFX()->CamSetPosition(v);
	mRendering.get()->getGFX()->CamSetRotation(fRot_x, fRot_y, fRot_z);


#pragma endregion

	if (DInputPC::getInstance().iskey(DIK_SPACE))
	{
		auto x = 5 - rand() % 10;
		auto y = 2 - rand() % 5;
		auto z = 5 - rand() % 10;
		hq->getTransform()->translate(dt*x, dt*y, dt*z);
	}

	//start imGui frame
	static int counter = 0;

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Transform:");

	std::string gameObjectName = hq->getName();
	Vector3 position = SceneManager::sGetInstance()->findObjectWithName(gameObjectName)->getTransform()->Position;
	Vector3 rotation = SceneManager::sGetInstance()->findObjectWithName(gameObjectName)->getTransform()->Rotation;
	Vector3 scale    = SceneManager::sGetInstance()->findObjectWithName(gameObjectName)->getTransform()->Scale;
	std::string  positionText = "Position : "+ std::to_string(position.x) + std::to_string(position.y) + std::to_string(position.z);
	std::string  rotationText = "Rotation : "+ std::to_string(rotation.x) + std::to_string(rotation.y) + std::to_string(rotation.z);
	std::string  scaleText = "Scale    : "+ std::to_string(scale.x) + std::to_string(scale.y) + std::to_string(scale.z);
	ImGui::Text(positionText.c_str());
	ImGui::Text(rotationText.c_str());
	ImGui::Text(scaleText.c_str());

	/*ImGui::Text("This is a text.");
	if (ImGui::Button("CLICK ME!"))
		counter += 1;
	std::string clickCount = "Click Count: " + std::to_string(counter);
	ImGui::Text(clickCount.c_str());*/

	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
	
	/*
	gameUI.Update();
	eui.update();
	*/


	//PostRender
	mRendering.get()->onPostRender(mTimer.getDeltaTIme());

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