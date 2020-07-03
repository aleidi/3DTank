#pragma once
#include "EngineCommon.h"

class Window
{
public:
	Window(HINSTANCE hInst);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window();

	bool processMessage();
	HWND getHwnd() const noexcept;
	HINSTANCE getHinst() const noexcept;
	POINT getCursorPosInWnd();

private:
	static LRESULT WINAPI handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI handleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	const wchar_t* mWndClassName;
	HWND mHwnd;
	HINSTANCE mHinst;
	bool mCanShowCursor;
	bool mCanClipCurosr;
};

