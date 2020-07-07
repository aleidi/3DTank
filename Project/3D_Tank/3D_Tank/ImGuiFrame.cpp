#include "ImGuiFrame.h"
#include "Vector3.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "KeycodeRedefine.h"
#include "Engine.h"

#include "AITank.h"
#include "AIController.h"
#include "SM_construction_fence.h"
#include "SM_WaterTank.h"
#include "SM_Crate.h"
#include "FreightContainer_A.h"

static std::map<std::string, bool> selectKey;
bool isNewAITank = false;
bool isNewFence = false;
bool isNewWaterTank = false;
bool isNewCrate = false;
bool isNewFreightContainer_A = false;
bool isNewFreightContainer_B = false;
bool isBindChanged = false;

void selectObject(std::string objectName);
void newObject(std::string gameObjectName);
void bindObjectTransform(std::string gameObjectName);

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
	static bool isToNew = false;     // create a new object
	static bool isVisiable = false;   // imGui window visible
	static bool isNameKeyInitial = false;

	//initial the nameKey
	if (!isNameKeyInitial)
	{	
		std::list<std::string> nameList = SceneManager::sGetInstance()->getAllGameobjectName();
		for (std::list<std::string>::iterator it = nameList.begin(); it != nameList.end(); ++it)
		{
			selectKey.insert(std::pair<std::string, bool>(*it, false));
		}
		isNameKeyInitial = true;
	}
	
	//visible operation by hotkey
	if (DInputPC::getInstance().iskey(HOTKEY))
	{
		isVisiable = false;
	}

	//is to close the frame or not
	if (!isVisiable)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Control Panel", nullptr, window_flags);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("New"))
			{
				ImGui::MenuItem("AI Tank", NULL, &isNewAITank);
				ImGui::MenuItem("Fence", NULL, &isNewFence);
				ImGui::MenuItem("Water Tank", NULL, &isNewWaterTank);
				ImGui::MenuItem("Crate", NULL, &isNewCrate);
				ImGui::MenuItem("Freight Container A", NULL, &isNewFreightContainer_A);
				ImGui::MenuItem("Freight Container B", NULL, &isNewFreightContainer_B);
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Select"))
			{
				std::list<std::string> nameList = SceneManager::sGetInstance()->getAllGameobjectName();
				for (std::list<std::string>::iterator it = nameList.begin(); it != nameList.end(); ++it)
				{
					selectObject(*it);
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Setting"))
			{
				ImGui::MenuItem("Hide the Window", NULL, &isVisiable);
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		//Select operation
		std::list<std::string> nameList = SceneManager::sGetInstance()->getAllGameobjectName();
		for (std::list<std::string>::iterator it = nameList.begin(); it != nameList.end(); ++it)
		{
			if (selectKey[*it])
			{
				bindObjectTransform(*it);

				static std::string attachNameStr;
				static char toAttachObjectName[32];
				ImGui::Text("Input Object name to attach:");
				ImGui::InputText("", toAttachObjectName, IM_ARRAYSIZE(toAttachObjectName));
				if (ImGui::Button("Attach"))
				{
					attachNameStr = toAttachObjectName;

					bool isInList = false;
					for (std::list<std::string>::iterator it2 = nameList.begin(); it2 != nameList.end(); ++it2)
					{
						if (attachNameStr == *it2)
							isInList = true;
					}
					if (isInList == true)
						SceneManager::sGetInstance()->findObjectWithName(*it)->attach(*SceneManager::sGetInstance()->findObjectWithName(attachNameStr));
				}
			}
		}

		//New operation
		isToNew = isNewAITank || isNewFence || isNewWaterTank || isNewCrate || isNewFreightContainer_A || isNewFreightContainer_B;
		if (isToNew)
		{
			static std::string nameStr;
			static char toNewObjectName[32];

			ImGui::Text("Set this new Object's name:");
			ImGui::InputText("", toNewObjectName, IM_ARRAYSIZE(toNewObjectName));
			if (ImGui::Button("Set Name"))
			{
				nameStr = toNewObjectName;
				newObject(toNewObjectName);
			}
		}

		ImGui::Text(" --------------------------------- ");
		if (ImGui::Button("Strat"))
		{
			Engine::sGetInstance()->enableGameMode(true);
		}
		ImGui::SameLine();
		if (ImGui::Button("Stop"))
		{
			Engine::sGetInstance()->enableGameMode(false);
		}
		ImGui::End();
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}


void selectObject(std::string objectName)
{
	char name[32];
	strcpy_s(name, objectName.c_str());
	ImGui::MenuItem(name, NULL, &selectKey[objectName]);

	static std::string presentSelectObject = "";
	if (presentSelectObject == "")
	{
		std::list<std::string> nameList = SceneManager::sGetInstance()->getAllGameobjectName();
		for (std::list<std::string>::iterator it = nameList.begin(); it != nameList.end(); ++it)
		{
			if (selectKey[*it])
			{
				presentSelectObject = *it;
				isBindChanged = true;
			}	
		}
	}
	else
	{
		std::list<std::string> nameList = SceneManager::sGetInstance()->getAllGameobjectName();
		for (std::list<std::string>::iterator it = nameList.begin(); it != nameList.end(); ++it)
		{
			if (selectKey[*it] && *it != presentSelectObject)
			{
				selectKey[presentSelectObject] = false;
				isBindChanged = true;
			}
		}
	}
}

void newObject(std::string gameObjectName)
{
	GameObject* newObject = nullptr;
	Vector3 position = Vector3(0, 0, 0);
	Vector3 scale = Vector3(0.01, 0.01, 0.01);
	Vector3 rotation = Vector3(0, 0, 0);
	if (isNewAITank)
	{
		static int id = 1;
		newObject = new AITank(id++);
		reinterpret_cast<AITank*>(newObject)->getCtrl()->wakeup();
		isNewAITank = false;
	}
	if (isNewFence)
	{
		newObject = new SM_construction_fence(position, rotation, scale);
		isNewFence = false;
	}
	if (isNewWaterTank)
	{
		newObject = new SM_WaterTank(position, rotation, scale);
		isNewWaterTank = false;
	}
	if (isNewCrate)
	{
		newObject = new SM_Crate(position, rotation, scale);
		isNewCrate = false;
	}
	if(isNewFreightContainer_A)
	{
		newObject = new FreightContainer_A(position, rotation, scale, 0);
		isNewFreightContainer_A = false;
	}
	if (isNewFreightContainer_B)
	{
		newObject = new FreightContainer_A(position, rotation, scale, 1);
		isNewFreightContainer_B = false;
	}
	newObject->setName(gameObjectName);
}

void bindObjectTransform(std::string gameObjectName)
{
	//search GameObject
	GameObject* gameObj = SceneManager::sGetInstance()->findObjectWithName(gameObjectName);

	static float positionOffset[3];
	static float rotationOffset[3];
	static float scaleOffset[3];
	if (isBindChanged)
	{
		positionOffset[0] = gameObj->getTransform()->getPosition().x;
		positionOffset[1] = gameObj->getTransform()->getPosition().y;
		positionOffset[2] = gameObj->getTransform()->getPosition().z;
		rotationOffset[0] = gameObj->getTransform()->getRotation().x;
		rotationOffset[1] = gameObj->getTransform()->getRotation().y;
		rotationOffset[2] = gameObj->getTransform()->getRotation().z;
		scaleOffset[0] = gameObj->getTransform()->getScale().x;
		scaleOffset[1] = gameObj->getTransform()->getScale().y;
		scaleOffset[2] = gameObj->getTransform()->getScale().z;
		isBindChanged = false;
	}

	//bind GameObject Transform
	ImGui::Text("Position:");
	gameObj->getTransform()->setPosition(Vector3(positionOffset[0], positionOffset[1], positionOffset[2]));
	ImGui::SliderFloat3("label 1", positionOffset, -50.0f, 50.0f);
	//range from -50.0f to 50.0f

	ImGui::Text("Rotation:");
	gameObj->getTransform()->setRotation(Vector3(rotationOffset[0], rotationOffset[1], rotationOffset[2]));
	ImGui::SliderFloat3("label 2", rotationOffset, -10.0f, 10.0f);
	
	ImGui::Text("Scale");
	gameObj->getTransform()->setScale(Vector3(scaleOffset[0], scaleOffset[1], scaleOffset[2]));
	ImGui::SliderFloat3("label 3", scaleOffset, -10.0f, 10.0f);
}