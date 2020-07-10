#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "EngineCommon.h"

class ImGuiFrame
{
public:
	ImGuiWindowFlags window_flags = 0;
	std::map<std::string, bool> selectKey;
	bool isNewAITank = false;
	bool isNewFence = false;
	bool isNewWaterTank = false;
	bool isNewCrate = false;
	bool isNewFreightContainer_A = false;
	bool isNewFreightContainer_B = false;
	bool isBindChanged = false;
	bool isChangeToNight = false;
	bool isChangeToSand = false;

	ImGuiFrame(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context);
	~ImGuiFrame();

	void onInit();
	void onUpdate(float deltaTime);

	void selectObject(std::string objectName);
	void newObject(std::string gameObjectName);
	void bindObjectTransform(std::string gameObjectName);
};