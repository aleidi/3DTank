#pragma once

#include <memory>
#include <vector>
#include <list>
#include <map>
#include "Windows.h"
#include "Configuration.h"
#include "Vector3.h"


#ifndef HR
#define HR(x) { hr = x; if( FAILED(hr) ) { return hr; } } 
#endif // !HR

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete(p); (p) = NULL; } }
#endif // !SAFE_DELETE

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = NULL; } }
#endif // !SAFE_RELEASE