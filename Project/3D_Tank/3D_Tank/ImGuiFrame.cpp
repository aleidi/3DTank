#include "ImGuiFrame.h"
#include "Vector3.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Transform.h"

static void createSomeThing();

ImGuiFrame::ImGuiFrame(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device, context);
	ImGui::StyleColorsDark();

	window_flags |= ImGuiWindowFlags_MenuBar;
}

ImGuiFrame::~ImGuiFrame()
{
}

void ImGuiFrame::onInit()
{

}
void ImGuiFrame::onUpdate(float deltaTime)
{
	static bool create_something = false;

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Transform:",nullptr, window_flags);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Create"))
		{
			ImGui::MenuItem("Tank", NULL, &create_something);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (create_something)
	{
		std::string gameObjectName = "hq"; //test code
		GameObject* hq = SceneManager::sGetInstance()->findObjectWithName(gameObjectName);

		createSomeThing();
		ImGui::Text("Position:");
	    static float positionOffset[3] = { 0,0,0 };
	    hq->getTransform()->setPosition(Vector3(positionOffset[0], positionOffset[1], positionOffset[2]));
	    ImGui::SliderFloat3("label position", positionOffset, -50.0f, 50.0f);
	
    	ImGui::Text("rotation:");
    	static float rotationOffset[3] = { 0,0,0 };
	    hq->getTransform()->setRotation(Vector3(rotationOffset[0], rotationOffset[1], rotationOffset[2]));
	    ImGui::SliderFloat3("label rotation", rotationOffset, -10.0f, 10.0f);
		
		/*ImGui::Text("Scale");
	    static float scaleOffset[3] = { 1,1,1 };
	    hq->getTransform()->setScale(Vector3(scaleOffset[0], scaleOffset[1], scaleOffset[2]));
	    ImGui::DragFloat3("3", scaleOffset, 0.3f, -50.0f, 50.0f);*/
	}

	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiFrame::startFrame()
{
	
}

static void createSomeThing()
{
	GameObject* obstacle = SceneManager::sGetInstance()->createSphere();
	obstacle->setName("obstacle");
	Vector3 pos(20.f, 10.f, 5.f);
	Vector3 scale(3.f, 3.f, 3.f);
	obstacle->getTransform()->setPosition(pos);
	obstacle->getTransform()->setScale(scale);
}