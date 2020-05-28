#include "Window.h"
#include "Engine.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	Window wnd(hInstance);

	Engine engine(wnd);

	engine.OnInit();

	while (wnd.processMessage())
	{
		engine.run();
	}
	
	return 0;
}


