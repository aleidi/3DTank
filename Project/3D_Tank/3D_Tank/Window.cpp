#include "Window.h"
#include "Engine.h"

#include <assert.h>

Window::Window(HINSTANCE hInst)
	:
	mWndClassName(WNDCLASSNAME), mHinst(hInst), mCanShowCursor(false), mCanClipCurosr(true)
{
	//ウィンドウクラスを定義して登録
	WNDCLASSEXW wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEXW);
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
	RegisterClassExW(&wndClass);

	RECT wr;
	wr.left = 100;
	wr.right = WINDOW_WIDTH + wr.left;
	wr.top = 100;
	wr.bottom = WINDOW_HEIGHT + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX, FALSE);

	//ウィンドウを作成
	mHwnd = CreateWindowW(mWndClassName, WNDTITLE, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, mHinst, this);

	ShowWindow(mHwnd, SW_SHOWDEFAULT);
	UpdateWindow(mHwnd);
}

Window::~Window()
{
	UnregisterClassW(mWndClassName, mHinst);
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
	//CreateWindow()から渡された生成パラメータを使用し、WinAPI側にウィンドウクラスのポインタを保存
	if (msg == WM_NCCREATE)
	{
		//生成データからウィンドウクラスのポインタを取得
		const CREATESTRUCTW* const pCreate = reinterpret_cast<const CREATESTRUCTW*>(lParam);
		Window* const pWnd = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		//有効性を確認
		assert(pWnd != nullptr);
		//WinAPI管理のユーザーデータにウィンドウクラスのポインタを保存
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//初期化完了後、メッセージプロシージャを通常のハンドラーへ切り替え
		SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::handleMsgThunk));
		//ウィンドウクラスのハンドラーへメッセージを転送
		return pWnd->handleMsg(hWnd, msg, wParam, lParam);
	}
	//WM_NCCREATEより前に受信したメッセージは既定のハンドラーで処理
	return DefWindowProcW(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::handleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//ウィンドウクラスのポインタを取得
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	//ウィンドウクラスのハンドラーへメッセージを転送
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

	return DefWindowProcW(hWnd, msg, wParam, lParam);
}
