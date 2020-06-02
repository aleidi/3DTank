#include "Window.h"
#include "Engine.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	Window wnd(hInstance);

	Engine::createSingleton(wnd);

	Engine::sGetInstance()->onInit();

	while (wnd.processMessage())
	{
		Engine::sGetInstance()->run();
	}
	
	Engine::sGetInstance()->Destroy();

	return 0;
}


