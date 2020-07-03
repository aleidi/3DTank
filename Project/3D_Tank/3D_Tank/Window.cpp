#include "Window.h"
#include "Engine.h"

#include <assert.h>

Window::Window(HINSTANCE hInst)
	:
	mWndClassName(WNDCLASSNAME), mHinst(hInst), mCanShowCursor(false), mCanClipCurosr(true)
{
	//define window class and register
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_CLASSDC;
	wndClass.lpfnWndProc = handleMsgSetup;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = mHinst;
	wndClass.hIcon = nullptr;
	wndClass.hCursor = nullptr;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = mWndClassName;
	RegisterClassEx(&wndClass);

	RECT wr;
	wr.left = 100;
	wr.right = WINDOW_WIDTH + wr.left;
	wr.top = 100;
	wr.bottom = WINDOW_HEIGHT + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX, FALSE);

	//create window
	mHwnd = CreateWindow(mWndClassName, WNDTITLE, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, mHinst, this);

	ShowWindow(mHwnd, SW_SHOWDEFAULT);
	UpdateWindow(mHwnd);
}

Window::~Window()
{
	UnregisterClass(mWndClassName, mHinst);
}

bool Window::processMessage()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			return false;
		}
	}
	return true;
}

HWND Window::getHwnd() const noexcept
{
	return mHwnd;
}

HINSTANCE Window::getHinst() const noexcept
{
	return mHinst;
}

POINT Window::getCursorPosInWnd()
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(mHwnd, &p);

	if (p.x < 0.0f)
	{
		p.x = 0.0f;
	}
	if (p.x > WINDOW_WIDTH)
	{
		p.x = WINDOW_WIDTH;
	}
	if (p.y < 0)
	{
		p.y = 0;
	}
	if (p.y > WINDOW_HEIGHT)
	{
		p.y = WINDOW_HEIGHT;
	}

	return p;
}


LRESULT WINAPI Window::handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		// sanity check
		assert(pWnd != nullptr);
		// set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::handleMsgThunk));
		// forward message to window class handler
		return pWnd->handleMsg(hWnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::handleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// retrieve ptr to window class
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window class handler
	return pWnd->handleMsg(hWnd, msg, wParam, lParam);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT Window::handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	if (mCanClipCurosr)
	{
		RECT rc;
		POINT tl{ 0,0 };
		ClientToScreen(mHwnd, &tl);
		GetClientRect(mHwnd, &rc);
		rc.left += tl.x;
		rc.right += tl.x;
		rc.top += tl.y;
		rc.bottom += tl.y;
		ClipCursor(&rc);
	}
	else
	{
		ClipCursor(NULL);
	}

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			DestroyWindow(hWnd);
			ClipCursor(NULL);
		}
		if (wParam == VK_F8)
		{
			ShowCursor(mCanShowCursor);
			mCanShowCursor = !mCanShowCursor;
		}
		if (wParam == VK_F9)
		{
			mCanClipCurosr = !mCanClipCurosr;
		}
		break;
	case WM_SIZE:
		if (Engine::sGetInstance() != nullptr)
		{
			Engine::sGetInstance()->onResize((float)LOWORD(lParam), (float)HIWORD(lParam));
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
