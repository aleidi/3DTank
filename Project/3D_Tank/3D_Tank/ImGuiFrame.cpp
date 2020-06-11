#include "ImGuiFrame.h"
#include "Vector3.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Transform.h"

static void createSomeThing();

GameObject* freightContainer_New;

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
	static bool isNew = false;     // create a new object
	static bool isDone = false;    // created
	static bool isVisiable = true; // imGui window visible


	if (isVisiable)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Strat Panel", nullptr, window_flags);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Create"))
			{
				ImGui::MenuItem("A New", NULL, &isNew);
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		if (isNew)
		{
			//std::string gameObjectName = "hq"; //test code
			//GameObject* hq = SceneManager::sGetInstance()->findObjectWithName(gameObjectName);
			if (!isDone)
			{
				createSomeThing();
				isDone = true;
			}
			ImGui::Text("Position:");
			static float positionOffset[3] = { freightContainer_New->getTransform()->getPosition().x,
											   freightContainer_New->getTransform()->getPosition().y,
											   freightContainer_New->getTransform()->getPosition().z };
			freightContainer_New->getTransform()->setPosition(Vector3(positionOffset[0], positionOffset[1], positionOffset[2]));
			ImGui::SliderFloat3("label 1", positionOffset, -50.0f, 50.0f);

			ImGui::Text("rotation:");
			static float rotationOffset[3] = { freightContainer_New->getTransform()->getRotation().x,
											   freightContainer_New->getTransform()->getRotation().y,
											   freightContainer_New->getTransform()->getRotation().z };
			freightContainer_New->getTransform()->setRotation(Vector3(rotationOffset[0], rotationOffset[1], rotationOffset[2]));
			ImGui::SliderFloat3("label 2", rotationOffset, -10.0f, 10.0f);

			/*ImGui::Text("Scale");
			static float scaleOffset[3] = { 1,1,1 };
			hq->getTransform()->setScale(Vector3(scaleOffset[0], scaleOffset[1], scaleOffset[2]));
			ImGui::DragFloat3("3", scaleOffset, 0.3f, -50.0f, 50.0f);*/
		}


		if (ImGui::Button("Finish!"))
			isVisiable = false;

		ImGui::End();
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}

void ImGuiFrame::startFrame()
{
	
}

static void createSomeThing()
{
	freightContainer_New = SceneManager::sGetInstance()->createEmptyObject();
	freightContainer_New->setName("freightContainer_A");
	SceneManager::sGetInstance()->createModel(*freightContainer_New, "Objects\\SM_FreightContainer_01", L"Objects\\TX_FreightContainer_01a_ALB");
	freightContainer_New->getTransform()->translate(Vector3::right*-20.0f);
	freightContainer_New->getTransform()->setScale(Vector3(0.025f, 0.025f, 0.025f));
}