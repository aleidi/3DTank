#include "ImGuiFrame.h"
#include "Vector3.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "KeycodeRedefine.h"

static std::map<std::string, bool> selectKey;
static bool isNewCube = false;
static bool isNewSphere = false;
static bool isNewPlane = false;

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
	static bool isVisiable = true;   // imGui window visible
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
		isVisiable = true;
	}

	//is to close the frame or not
	if (isVisiable)
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
			ImGui::EndMenuBar();
		}

		//select bind operation
		std::list<std::string> nameList = SceneManager::sGetInstance()->getAllGameobjectName();
		for (std::list<std::string>::iterator it = nameList.begin(); it != nameList.end(); ++it)
		{
			if (selectKey[*it])
			{
				bindObjectTransform(*it);
			}
		}

		//new operation
		isToNew = isNewCube || isNewSphere || isNewPlane;
		if (isToNew)
		{
			static std::string nameStr;
			static char toNewObjectName[32];

			ImGui::Text("Set this new Object's name:");
			ImGui::InputText("label name", toNewObjectName, IM_ARRAYSIZE(toNewObjectName));
			if (ImGui::Button("Set Name"))
			{
				nameStr = toNewObjectName;
				newObject(toNewObjectName);
			}

		}
				
		if (ImGui::Button("Finish!"))
			isVisiable = false;

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

	/*GameObject* freightContainer_New = SceneManager::sGetInstance()->createEmptyObject();
	freightContainer_New->setName(gameObjectName);
	SceneManager::sGetInstance()->createModel(*freightContainer_New, "Objects\\SM_FreightContainer_01", L"Objects\\TX_FreightContainer_01a_ALB");
	freightContainer_New->getTransform()->translate(Vector3::right*-20.0f);
	freightContainer_New->getTransform()->setScale(Vector3(0.025f, 0.025f, 0.025f));*/
}

void bindObjectTransform(std::string gameObjectName)
{
	//search GameObject
	GameObject* gameObj = SceneManager::sGetInstance()->findObjectWithName(gameObjectName);

	//bind GameObject Transform
	ImGui::Text("Position:");
	static float positionOffset[3] = { gameObj->getTransform()->getPosition().x,
									   gameObj->getTransform()->getPosition().y,
									   gameObj->getTransform()->getPosition().z };
	gameObj->getTransform()->setPosition(Vector3(positionOffset[0], positionOffset[1], positionOffset[2]));
	ImGui::SliderFloat3("label 1", positionOffset, -50.0f, 50.0f);

	ImGui::Text("Rotation:");
	static float rotationOffset[3] = { gameObj->getTransform()->getRotation().x,
									   gameObj->getTransform()->getRotation().y,
									   gameObj->getTransform()->getRotation().z };
	gameObj->getTransform()->setRotation(Vector3(rotationOffset[0], rotationOffset[1], rotationOffset[2]));
	ImGui::SliderFloat3("label 2", rotationOffset, -10.0f, 10.0f);
	
	ImGui::Text("Scale");
	static float scaleOffset[3] = { gameObj->getTransform()->getScale().x,
									gameObj->getTransform()->getScale().y,
									gameObj->getTransform()->getScale().z };
	gameObj->getTransform()->setScale(Vector3(scaleOffset[0], scaleOffset[1], scaleOffset[2]));
	ImGui::SliderFloat3("label 3", scaleOffset, -10.0f, 10.0f);
}