#include <sstream>
#include "Engine.h"
#include "Window.h"
#include "SceneManager.h"
#include "ComponentFactory.h"
#include "Configuration.h"
#include "Rendering.h"
#include "Graphics.h"

#include "Collision.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

Engine* Engine::sInstance = nullptr;

//test code

Collision* collision;

static float dis = 0.0f;

Engine::Engine(Window& wnd)
	:
	mWnd(wnd),
	mSound(std::make_unique<Sound>()),
	mRendering(std::make_unique<Rendering>(wnd)),
	mGameSystem(std::make_unique<GameSystem>()),
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
	//Input Init
	DInputPC::getInstance().onInit(mWnd.getHwnd(), mWnd.getHinst(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	//Sound Init
	mSound->onInit();


	//Gui Init

	//EUI Init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(mWnd.getHwnd());
	ImGui_ImplDX11_Init(mRendering->getGFX()->GetDevice(), mRendering->getGFX()->GetContext());
	ImGui::StyleColorsDark();

	//Game Init
	mGameSystem->onInit();
#pragma region TestCode

	//test code
	 fScale = 1.0f;
	 fTrans_x = 0.0f;
	 fTrans_y = 0.0f;
	 fTrans_z = 0.0f;
	 fRot_x = 0.0f;
	 fRot_y = 0.0f;
	 fRot_z = 0.0f;
	 fspeed = 300.0f;
	 rspeed = 5.0f;



	//GameObject* obstacle = SceneManager::sGetInstance()->createSphere();
	//obstacle->setName("obstacle");
	//Vector3 pos(20.f, 5.f, 5.f);
	//Vector3 scale(3.f, 3.f, 3.f);
	//obstacle->getTransform()->setPosition(pos);
	//obstacle->getTransform()->setScale(scale);
	//collision = new Collision();
	//float radius = 5.f;
	//collision->createSphere(obstacle->getTransform()->getLocalPosition(),radius);
	//Vector3 extents(10.f, 10.f, 10.f);
	//collision->createCube(hq->getTransform()->getPosition(), extents);

	//hq->setLastFramePosition(hq->getTransform()->getPosition());

#pragma endregion

	
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
	SceneManager::sGetInstance()->onEngineFixedUpdate(FixedDeltaTime);

	//Game Update

	SceneManager::sGetInstance()->onEngineUpdate(deltaTime);

	if (mIsGameMode)
	{
		mGameSystem->onUpdate(deltaTime);
		mSound->playBGM();
	}
	//collision->transformCube(collision->mCube[0], hq->getTransform()->getPosition());
	//bool isCollision = collision->cubeCollisionSphere(collision->mCube[0], collision->mSphere[0]);
	//if (isCollision) {
	//	mSound->setPause(MusicIndex(BGM));
	//	hq->setLastFramePosition(hq->getLastFramePosition());
	//	hq->getTransform()->setPosition(hq->getLastFramePosition());
	//}
	//else {
	//	mSound->setReplay(MusicIndex(BGM));
	//	hq->setLastFramePosition(hq->getTransform()->getPosition());
	//}

#pragma region test code

	if (DInputPC::getInstance().iskeyDown(DIK_SPACE))
	{
		mIsGameMode = true;
	}

#pragma endregion


	//Sound Update
	dis += fTrans_z;
	mSound->onUpdate(dis);

	//PreRender
	mRendering.get()->onPreRender(deltaTime);

	//OnRender
	mRendering.get()->onRender(deltaTime);

	//PostRender
	mRendering.get()->onPostRender(deltaTime);
	
	/*
	gameUI.Update();
	eui.update();
	*/

	//EUI Update

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