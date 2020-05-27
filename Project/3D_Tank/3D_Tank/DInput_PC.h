#pragma once

#include <dinput.h>
#include <memory.h>
#include "EnginePlat.h"

class DInputPC {
public:
	DInputPC();
	~DInputPC();

	// static DInputPC& getInstance();

	////////////////////////////////////////////
	HRESULT initialize(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags); // initialize DirectInput keyboard & mouse
	void getInput();
	bool iskeyDown(int iKey);

	bool isMouseButtonDown(int button);
	float mouseDX();
	float mouseDY();
	float mouseDZ();

private:
	IDirectInput8 *m_pDirectInput;
	IDirectInputDevice8 * m_KeyboardDevice;
	char m_keyBuffer[256];
	char m_prekeyBuffer[256];

	IDirectInputDevice8 * m_MouseDevice;
	DIMOUSESTATE m_MouseState;

	////////////////// singleton///////////////////////
		// DInputPC();
		// ~DInputPC();
		// DInputPC(const DInputPC& other);
};



