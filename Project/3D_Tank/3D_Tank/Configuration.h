#pragma once

//defien resoultion
#define  RES720

#ifdef RES720
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#endif // 720P

#define WNDCLASSNAME L"Main Window"
#define WNDTITLE L"3D Tank"

#if defined(PS4)
#include "DInput_PS4.h"
#else
#include "DInput_PC.h"
#endif
