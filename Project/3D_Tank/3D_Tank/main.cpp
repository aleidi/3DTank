#include "Window.h"
#include "Engine.h"

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	Window wnd(hInstance);

	Engine::createSingleton(wnd);

	while (wnd.processMessage())
	{
		Engine::sGetInstance()->run();
	}

	Engine::sGetInstance()->Destroy();

	return 0;
}


