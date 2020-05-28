#pragma once

#include <dinput.h>
#include <memory.h>
#include "EngineCommon.h"

class DInputPC {
public:
	// DInputPC();
	// ~DInputPC();

	static DInputPC& getInstance();

	////////////////////////////////////////////
	HRESULT onInit(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags); // initialize DirectInput keyboard & mouse

	void onUpdate();
	void getInput();
	bool iskey(int iKey);
	bool iskeyDown(int iKey);
	bool iskeyUp(int iKey);

	bool isMouseButton(int button);
	bool isMouseButtonDown(int button);
	bool isMouseButtonUp(int button);
	float mouseDX();
	float mouseDY();
	float mouseDZ();

private:
	IDirectInput8 *m_pDirectInput;
	IDirectInputDevice8 * m_KeyboardDevice;
	char m_keyBuffer[256];
	char pre_keyBuffer[256];

	IDirectInputDevice8 * m_MouseDevice;
	DIMOUSESTATE m_MouseState;
	BYTE    pre_rgbButtons[4];

	////////////////// singleton///////////////////////
	DInputPC();
	~DInputPC();
		// DInputPC(const DInputPC& other);
};



