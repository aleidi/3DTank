#include "DInput_PC.h"

DInputPC::DInputPC() {
	m_pDirectInput = NULL;
	m_KeyboardDevice = NULL;
	ZeroMemory(m_keyBuffer, sizeof(char) * 256);
	m_MouseDevice = NULL;
	ZeroMemory(&m_MouseState, sizeof(m_MouseState));
}

DInputPC::~DInputPC() {
	if (m_KeyboardDevice != NULL)
		m_KeyboardDevice->Unacquire();
	if (m_MouseDevice != NULL)
		m_MouseDevice->Unacquire();
	SAFE_RELEASE(m_KeyboardDevice);
	SAFE_RELEASE(m_MouseDevice);
	SAFE_RELEASE(m_pDirectInput);
}

// DInputPC::DInputPC(const DInputPC& other) {}

HRESULT DInputPC::initialize(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags) {
	HRESULT hr;

	HR(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	//initialize keyboard
	HR(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_KeyboardDevice, NULL));
	HR(m_KeyboardDevice->SetCooperativeLevel(hWnd, keyboardCoopFlags));
	HR(m_KeyboardDevice->SetDataFormat(&c_dfDIKeyboard));
	HR(m_KeyboardDevice->Acquire());
	HR(m_KeyboardDevice->Poll());

	//initialie mouse
	HR(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_MouseDevice, NULL));
	HR(m_MouseDevice->SetCooperativeLevel(hWnd, mouseCoopFlags));
	HR(m_MouseDevice->SetDataFormat(&c_dfDIMouse));
	HR(m_MouseDevice->Acquire());
	HR(m_MouseDevice->Poll());

	return S_OK;
}

void DInputPC::getInput() {
	HRESULT hr = m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer);
	// get keyboard input
	if (hr) {
		m_KeyboardDevice->Acquire();
		m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (LPVOID)m_keyBuffer);
	}


	hr = m_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**)&m_MouseState);
	// get mouse input
	if (hr) {
		m_MouseDevice->Acquire();
		m_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**)&m_MouseState);
	}
}

bool DInputPC::iskeyDown(int iKey) {
	if (m_keyBuffer[iKey] & 0x80)
		return true;
	else
		return false;
}

bool DInputPC::isMouseButtonDown(int button) {
	return(m_MouseState.rgbButtons[button] & 0x80) != 0;
}

float DInputPC::mouseDX() {
	return(float)m_MouseState.lX;
}

float DInputPC::mouseDY() {
	return(float)m_MouseState.lY;
}

float DInputPC::mouseDZ() {
	return(float)m_MouseState.lZ;
}



////////////////// singleton///////////////////////

/*
static DInputPC& DInputPC::getInstance() {
	static DInputPC m_DInputPC;
	return m_DInputPC;
}
*/




