#include "ImGuiFrame.h"
#include "string"
#include "GameObject.h"

ImGuiFrame::ImGuiFrame(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device, context);
	ImGui::StyleColorsDark();
}

ImGuiFrame::~ImGuiFrame()
{
}

void ImGuiFrame::onInit()
{

}
void ImGuiFrame::onUpdate(float deltaTime)
{
}

void ImGuiFrame::startFrame()
{
	//ImGui_ImplDX11_NewFrame();
	//ImGui_ImplWin32_NewFrame();
	//ImGui::NewFrame();
	//ImGui::Begin("Transform:");

	//std::string gameObjectName = hq->getName();
	//ImGui::Text("Position:");
	//static float positionOffset[3] = { 0,0,0 };
	//ImGui::DragFloat3("", positionOffset, 0.3f, -50.0f, 50.0f);
	//hq->getTransform()->setPosition(Vector3(positionOffset[0], positionOffset[1], positionOffset[2]));
	///*static float rotationOffset[3] = { 0,0,0 };
	//ImGui::DragFloat3("", positionOffset, 0.3f, -50.0f, 50.0f);

	//static float scaleOffset[3] = { 0,0,0 };
	//ImGui::DragFloat3("", positionOffset, 0.3f, -50.0f, 50.0f);*/

	//ImGui::End();
	//ImGui::Render();
	//ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}