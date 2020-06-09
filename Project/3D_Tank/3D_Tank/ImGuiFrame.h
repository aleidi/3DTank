#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "Vector3.h"
#include "EngineCommon.h"

class ImGuiFrame
{
public:
	ImGuiFrame(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context);
	~ImGuiFrame();

	void onInit();
	void onUpdate(float deltaTime);
	void startFrame();
};