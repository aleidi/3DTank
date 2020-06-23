#include "ImGuiFrame.h"
#include "Vector3.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "KeycodeRedefine.h"
#include "Engine.h"

static std::map<std::string, bool> selectKey;
static bool isNewCube = false;
static bool isNewSphere = false;
static bool isNewPlane = false;
static bool isBindChanged = false;

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
				ImGui::MenuItem("Cube", NULL, &isNewCube);
				ImGui::MenuItem("Sphere", NULL, &isNewSphere);
				ImGui::MenuItem("Plane", NULL, &isNewPlane);
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
		isToNew = isNewCube || isNewSphere || isNewPlane;
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
	if (isNewCube)
	{
		newObject = SceneManager::sGetInstance()->createCube();
		isNewCube = false;
	}
	if (isNewSphere)
	{
		newObject = SceneManager::sGetInstance()->createSphere();
		isNewSphere = false;
	}
	if (isNewPlane)
	{
		newObject = SceneManager::sGetInstance()->createPlane();
		isNewPlane = false;
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