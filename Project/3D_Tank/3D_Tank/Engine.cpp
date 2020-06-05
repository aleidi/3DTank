#include <sstream>
#include "Engine.h"
#include "Window.h"
#include "SceneManager.h"
#include "ComponentFactory.h"

#include "GameObject.h"
#include "Transform.h"
#include "ModelMesh.h"
#include "TankGamePlay.h"
#include "TankBatteryCtrl.h"
#include "Camera.h"
#include "CameraCtrl.h"

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
GameObject* cam;
GameObject* follow;

static float dis = 0.0f;

Engine::Engine(Window& wnd)
	:
	mWnd(wnd),
	mSound(std::make_unique<Sound>()),
	mRendering(std::make_unique<Rendering>(wnd)),
	mIsGameMode(false)
{
	onPreInit();

	onInit();
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

	//Gui Init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(mWnd.getHwnd());
	ImGui_ImplDX11_Init(mRendering->getGFX()->GetDevice(), mRendering->getGFX()->GetContext());
	ImGui::StyleColorsDark();

	//EUI Init

	//Game Init
	//SceneManager::sGetInstance()

	//test code
	hq = SceneManager::sGetInstance()->createEmptyObject();
	hq->setName("hq");
	ScriptComponent* sc = new TankGamePlay(hq);
	hq->addScriptComponent(sc);
	
	follow = SceneManager::sGetInstance()->createEmptyObject();
	follow->setName("follow");
	follow->attach(*hq);
	follow->getTransform()->translate(0.0f, 20.0f, -40.0f);

	cam = SceneManager::sGetInstance()->createEmptyObject();
	cam->setName("camera");
	Camera* maincam = new Camera(cam);
	cam->addComponent(maincam);
	maincam->MainCamera = maincam;
	cam->addComponent(new CameraCtrl(cam));
	cam->getTransform()->rotateX(20);

	tankBattery = SceneManager::sGetInstance()->createEmptyObject();
	tankBattery->setName("tankBattery");
	SceneManager::sGetInstance()->createModel(*tankBattery, "Tank\\TankBattery", L"Tank\\TankTex");
	tankBattery->attach(*hq);
	ScriptComponent* sc2 = new TankBatteryCtrl(tankBattery);
	tankBattery->addScriptComponent(sc2);

	tankBody = SceneManager::sGetInstance()->createEmptyObject();
	tankBody->setName("tankBody");
	SceneManager::sGetInstance()->createModel(*tankBody, "Tank\\TankBody", L"Tank\\TankTex");
	tankBody->attach(*hq);

	tankTrackL = SceneManager::sGetInstance()->createEmptyObject();
	tankTrackL->setName("tankTrackL");
	SceneManager::sGetInstance()->createModel(*tankTrackL, "Tank\\TankTrack_L", L"Tank\\TankTrack");
	tankTrackL->attach(*hq);

	tankTrackR = SceneManager::sGetInstance()->createEmptyObject();
	tankTrackR->setName("tankTrackR");
	SceneManager::sGetInstance()->createModel(*tankTrackR, "Tank\\TankTrack_R", L"Tank\\TankTrack");
	tankTrackR->attach(*hq);

	GameObject* ground = SceneManager::sGetInstance()->createEmptyObject();
	ground->setName("Ground");
	SceneManager::sGetInstance()->createModel(*ground, "Objects\\SM_ZPlane_01a", L"Objects\\TX_RockyMud_01_ALB");

	hq->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));
}

void Engine::run()
{
	//Timer update
	mTimer.tick();
	float deltaTime = mTimer.getDeltaTIme();
	calculateFrameStats();

	//Input Update
	DInputPC::getInstance().onUpdate();

	//Physics Update

	//Game Update
	SceneManager::sGetInstance()->onEngineUpdate(deltaTime);
	if (mIsGameMode)
	{
		SceneManager::sGetInstance()->onUpdate(deltaTime);
	}

	//Sound Update
	dis += fTrans_z;
	mSound->onUpdate(dis);

	//PreRender
	mRendering.get()->onPreRender(deltaTime);

	//OnRender
	mRendering.get()->onRender(deltaTime);

#pragma region test code
	float dt = mTimer.getDeltaTIme() * fspeed;
	float dt2 = mTimer.getDeltaTIme() * rspeed;
	//XMVECTOR v = mRendering.get()->getGFX()->getCamPos();
	//if (DInputPC::getInstance().iskey(DIK_W))
	//{
	//	v = mRendering.get()->getGFX()->getcamForward();
	//	v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
	//	v = XMVectorAdd(mRendering.get()->getGFX()->getCamPos(), v);
	//}
	//if (DInputPC::getInstance().iskey(DIK_S))
	//{
	//	v = mRendering.get()->getGFX()->getcamForward();
	//	v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
	//	v = XMVectorSubtract(mRendering.get()->getGFX()->getCamPos(),v);

	//}
	//if (DInputPC::getInstance().iskey(DIK_A))
	//{
	//	v = mRendering.get()->getGFX()->getcamRight();
	//	v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
	//	v = XMVectorSubtract(mRendering.get()->getGFX()->getCamPos(), v);
	//}
	//if (DInputPC::getInstance().iskey(DIK_D))
	//{
	//	v = mRendering.get()->getGFX()->getcamRight();
	//	v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
	//	v = XMVectorAdd(mRendering.get()->getGFX()->getCamPos(), v);
	//}
	//if (DInputPC::getInstance().iskey(DIK_Q))
	//{
	//	v = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//	v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
	//	v = XMVectorAdd(mRendering.get()->getGFX()->getCamPos(), v);
	//}
	//if (DInputPC::getInstance().iskey(DIK_E))
	//{
	//	v = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);
	//	v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
	//	v = XMVectorAdd(mRendering.get()->getGFX()->getCamPos(), v);
	//}
	//if (DInputPC::getInstance().iskey(DIK_I))
	//{
	//	fRot_x -= mTimer.getDeltaTIme() * rspeed;
	//}
	//if (DInputPC::getInstance().iskey(DIK_K))
	//{
	//	fRot_x += mTimer.getDeltaTIme() * rspeed;
	//}
	//if (DInputPC::getInstance().iskey(DIK_J))
	//{
	//	fRot_y -= mTimer.getDeltaTIme() * rspeed;
	//}
	//if (DInputPC::getInstance().iskey(DIK_L))
	//{
	//	fRot_y += mTimer.getDeltaTIme() * rspeed;
	//}
	//if (DInputPC::getInstance().iskey(DIK_U))
	//{
	//	fRot_z -= mTimer.getDeltaTIme() * rspeed;
	//}
	//if (DInputPC::getInstance().iskey(DIK_O))
	//{
	//	fRot_z += mTimer.getDeltaTIme() * rspeed;
	//}
	//mRendering.get()->getGFX()->CamSetPosition(v);
	//mRendering.get()->getGFX()->CamSetRotation(fRot_x, fRot_y, fRot_z);

	if (DInputPC::getInstance().iskeyDown(DIK_SPACE))
	{
		mIsGameMode = true;
	}

#pragma endregion

	//PostRender
	mRendering.get()->onPostRender(mTimer.getDeltaTIme());

	//start imGui frame
	static int counter = 0;

	//ImGui_ImplDX11_NewFrame();
	//ImGui_ImplWin32_NewFrame();
	//ImGui::NewFrame();
	//ImGui::Begin("Transform:");

	//std::string gameObjectName = hq->getName();
	//Vector3 position = SceneManager::sGetInstance()->findObjectWithName(gameObjectName)->getTransform()->getPosition();
	//Vector3 rotation = SceneManager::sGetInstance()->findObjectWithName(gameObjectName)->getTransform()->getRotation();
	//Vector3 scale    = SceneManager::sGetInstance()->findObjectWithName(gameObjectName)->getTransform()->getScale();
	//std::string  positionText = "Position : "+ std::to_string(position.x) + std::to_string(position.y) + std::to_string(position.z);
	//std::string  rotationText = "Rotation : "+ std::to_string(rotation.x) + std::to_string(rotation.y) + std::to_string(rotation.z);
	//std::string  scaleText = "Scale    : "+ std::to_string(scale.x) + std::to_string(scale.y) + std::to_string(scale.z);
	//ImGui::Text(positionText.c_str());
	//ImGui::Text(rotationText.c_str());
	//ImGui::Text(scaleText.c_str());

	/*ImGui::Text("This is a text.");
	if (ImGui::Button("CLICK ME!"))
		counter += 1;
	std::string clickCount = "Click Count: " + std::to_string(counter);
	ImGui::Text(clickCount.c_str());*/

	//ImGui::End();
	//ImGui::Render();
	//ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
	
	/*
	gameUI.Update();
	eui.update();
	*/


	mRendering.get()->onEndRender(deltaTime);
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