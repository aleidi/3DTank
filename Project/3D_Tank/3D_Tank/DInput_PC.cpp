#include "DInput_PC.h"
#include "Engine.h"

DInputPC::DInputPC() {
	m_pDirectInput = NULL;
	m_KeyboardDevice = NULL;
	ZeroMemory(m_keyBuffer, sizeof(char) * 256);
	ZeroMemory(pre_keyBuffer, sizeof(char) * 256);
	m_MouseDevice = NULL;
	ZeroMemory(&m_MouseState, sizeof(m_MouseState));
	ZeroMemory(pre_rgbButtons, sizeof(BYTE) * 4);
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

HRESULT DInputPC::onInit(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags) {
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

void DInputPC::onUpdate() {

	//// copykeybuffer
	int k = 0;
	for (auto& buff : pre_keyBuffer)
	{
		buff = m_keyBuffer[k];
		++k;
	}
	// copymousebuffer
	for (int i = 0; i < 4; i++) {
		pre_rgbButtons[i] = m_MouseState.rgbButtons[i];
	} 
	DInputPC::getInput();


	int num = 10086;
	Engine::sGetInstance()->showtText(std::to_wstring(num), 0, 0, 300, 300, false);
	Engine::sGetInstance()->showtText(L"asdsdaasdasda",0,0,300,300,false);
}

void DInputPC::getInput() {
	HRESULT hr = m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer);
	// get keyboard input
	if (hr) {
		m_KeyboardDevice->Acquire();
		m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (LPVOID)m_keyBuffer);
	}

	hr = m_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**)&m_MouseState); // Exception thrown: read access violation.	this->m_MouseDevice was nullptr. ?
	// get mouse input
	if (hr) {
		m_MouseDevice->Acquire();
		m_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**)&m_MouseState);
	}
}

bool DInputPC::iskey(int iKey) {
	return (m_keyBuffer[iKey] & 0x80);
}

bool DInputPC::iskeyDown(int iKey) {
	return (!(pre_keyBuffer[iKey] & 0x80) && iskey(iKey));
}

bool DInputPC::iskeyUp(int iKey) {
	return ((pre_keyBuffer[iKey] & 0x80) && !iskey(iKey));
}

bool DInputPC::isMouseButton(int button) {
	return(m_MouseState.rgbButtons[button] & 0x80) != 0;
}

bool DInputPC::isMouseButtonDown(int button) {
	return (((pre_rgbButtons[button] & 0x80) == 0) && isMouseButton(button));
}

bool DInputPC::isMouseButtonUp(int button) {
	return (((pre_rgbButtons[button] & 0x80) != 0) && !isMouseButton(button));
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

DInputPC& DInputPC::getInstance() {
	static DInputPC m_DInputPC;
	return m_DInputPC;
}





