#pragma once

#include <memory>
#include "Windows.h"
#include "Configuration.h"

namespace EngineRender
{
	enum MeshType
	{
		BOX,
		Sphere,
		Plane
	};
}

#ifndef HR
#define HR(x) { hr = x; if( FAILED(hr) ) { return hr; } } 
#endif // !HR 自定义的HR宏，方便执行错误的返回

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete(p); (p) = NULL; } }
#endif // !SAFE_DELETE 自定义的SAFE_DELETE()宏，便于指针释放

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = NULL; } }
#endif // !SAFE_RELEASE 自定义的SAFE_RELEASE()宏，便于COM资源的释放