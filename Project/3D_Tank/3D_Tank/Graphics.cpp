#include <cassert>
#include <math.h>
#include <d3dcompiler.h>
#include "dxgi1_2.h"
#include "dxgi.h"
#include "Window.h"
#include "Graphics.h"
#include "RenderCamera.h"
#include "DXTrace.h"
#include "d3dUtil.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dCompiler.lib")
#pragma comment(lib, "winmm.lib")

namespace Colors
{
	XMFLOAT4 White = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMFLOAT4 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	XMFLOAT4 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	XMFLOAT4 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	XMFLOAT4 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	XMFLOAT4 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	XMFLOAT4 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
	XMFLOAT4 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };

	XMFLOAT4 Silver = { 0.75f, 0.75f, 0.75f, 1.0f };
	XMFLOAT4 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
}

Graphics::Graphics(const Window& wnd)
	:
	mhMainWnd(wnd.getHwnd()), mCanShowText(false),
	m4xMsaaQuality(0),mEnable4xMsaa(false),
	mRenderCamera(std::make_unique<RenderCamera>(*this))
{
	InitD3D();

	InitD2D();
}

Graphics::~Graphics()
{

}

ID3D11Device* Graphics::GetDevice() const
{
	return pDevice.Get();
}

ID3D11DeviceContext* Graphics::GetContext() const
{
	return pContext.Get();
}

bool Graphics::InitD3D()
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(mhMainWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	mClientWidth = width;
	mClientHeight = height;

	// ´´½¨D3DÉè±¸ ºÍ D3DÉè±¸ÉÏÏÂÎÄ
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// Çý¶¯ÀàÐÍÊý×é
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	// ÌØÐÔµÈ¼¶Êý×é
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_FEATURE_LEVEL featureLevel;
	D3D_DRIVER_TYPE d3dDriverType;
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		d3dDriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(nullptr, d3dDriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, pDevice.GetAddressOf(), &featureLevel, pContext.GetAddressOf());

		if (hr == E_INVALIDARG)
		{
			// Direct3D 11.0 µÄAPI²»³ÐÈÏD3D_FEATURE_LEVEL_11_1£¬ËùÒÔÎÒÃÇÐèÒª³¢ÊÔÌØÐÔµÈ¼¶11.0ÒÔ¼°ÒÔÏÂµÄ°æ±¾
			hr = D3D11CreateDevice(nullptr, d3dDriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
				D3D11_SDK_VERSION, pDevice.GetAddressOf(), &featureLevel, pContext.GetAddressOf());
		}

		if (SUCCEEDED(hr))
			break;
	}

	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0 && featureLevel != D3D_FEATURE_LEVEL_11_1)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	pDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	assert(m4xMsaaQuality > 0);

	Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory1> dxgiFactory1 = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory2 = nullptr;

	HRD(pDevice.As(&dxgiDevice));
	HRD(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));
	HRD(dxgiAdapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(dxgiFactory1.GetAddressOf())));

	hr = dxgiFactory1.As(&dxgiFactory2);

	if (dxgiFactory2 != nullptr)
	{
		HRD(pDevice.As(&pDevice1));
		HRD(pContext.As(&pContext1));

		DXGI_SWAP_CHAIN_DESC1 sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.Width = width;
		sd.Height = height;
		sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		if (mEnable4xMsaa)
		{
			sd.SampleDesc.Count = 4;
			sd.SampleDesc.Quality = m4xMsaaQuality - 1;
		}
		else
		{
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
		}
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fd;
		fd.RefreshRate.Numerator = 60;
		fd.RefreshRate.Denominator = 1;
		fd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		fd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		fd.Windowed = TRUE;

		HRD(dxgiFactory2->CreateSwapChainForHwnd(pDevice.Get(), mhMainWnd, &sd, &fd, nullptr, pSwapChain1.GetAddressOf()));
		HRD(pSwapChain1.As(&pSwapChain));
	}
	else
	{
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		if (mEnable4xMsaa)
		{
			sd.SampleDesc.Count = 4;
			sd.SampleDesc.Quality = m4xMsaaQuality - 1;
		}
		else
		{
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
		}
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = mhMainWnd;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;
		HRD(dxgiFactory1->CreateSwapChain(pDevice.Get(), &sd, pSwapChain.GetAddressOf()));
	}

	ID3D11Texture2D* pBackBuffer;

	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView(pBackBuffer, 0, pRenderTargetView.GetAddressOf());
	pBackBuffer->Release();

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = mClientWidth;
	depthStencilDesc.Height = mClientWidth;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	pDevice->CreateTexture2D(&depthStencilDesc, 0, pDepthStencilBuffer.GetAddressOf());
	pDevice->CreateDepthStencilView(pDepthStencilBuffer.Get(), 0, pDepthStencilView.GetAddressOf());

	pContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), pDepthStencilView.Get());

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.FrontCounterClockwise = false;
	rd.DepthClipEnable = true;
	pDevice->CreateRasterizerState(&rd, pRasterizerState.GetAddressOf());
	pContext->RSSetState(pRasterizerState.Get());

	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = static_cast<float>(width);
	vp.Height = static_cast<float>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	dxgiFactory1->MakeWindowAssociation(mhMainWnd, DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);

	pContext->RSSetViewports(1, &vp);

	return true;
}

bool Graphics::InitD2D()
{
	HRD(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, pd2dFactory.GetAddressOf()));
	HRD(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(pWriteFactory.GetAddressOf())));

	BindD2DResource();

	return true;
}

void Graphics::BindD2DResource()
{
	assert(pd2dFactory);
	assert(pd2dFactory);

	pColorBrush.Reset();
	pd2dRenderTarget.Reset();

	Microsoft::WRL::ComPtr<IDXGISurface> surface;
	HRD(pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), reinterpret_cast<void**>(surface.GetAddressOf())));
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
	HRESULT hr = pd2dFactory->CreateDxgiSurfaceRenderTarget(surface.Get(), &props, pd2dRenderTarget.GetAddressOf());
	surface.Reset();

	if (hr == E_NOINTERFACE)
	{
		OutputDebugStringW(L"\n¾¯¸æ£ºDirect2DÓëDirect3D»¥²Ù×÷ÐÔ¹¦ÄÜÊÜÏÞ£¬Äã½«ÎÞ·¨¿´µ½ÎÄ±¾ÐÅÏ¢¡£ÏÖÌá¹©ÏÂÊö¿ÉÑ¡·½·¨£º\n"
			L"1. ¶ÔÓÚWin7ÏµÍ³£¬ÐèÒª¸üÐÂÖÁWin7 SP1£¬²¢°²×°KB2670838²¹¶¡ÒÔÖ§³ÖDirect2DÏÔÊ¾¡£\n"
			L"2. ×ÔÐÐÍê³ÉDirect3D 10.1ÓëDirect2DµÄ½»»¥¡£ÏêÇé²ÎÔÄ£º"
			L"https://docs.microsoft.com/zh-cn/windows/desktop/Direct2D/direct2d-and-direct3d-interoperation-overview""\n"
			L"3. Ê¹ÓÃ±ðµÄ×ÖÌå¿â£¬±ÈÈçFreeType¡£\n\n");
	}
	else if (hr == S_OK)
	{
		HRD(pd2dRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			pColorBrush.GetAddressOf()));
		HRD(pWriteFactory->CreateTextFormat(L"黑体", nullptr, DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"zh-cn",
			pTextFormat.GetAddressOf()));
	}
	else
	{
		assert(pd2dRenderTarget);
	}
}

void Graphics::BindD3DResource()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	HRD(pSwapChain->ResizeBuffers(1, mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	HRD(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));
	HRD(pDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, pRenderTargetView.GetAddressOf()));

	D3D11SetDebugObjectName(backBuffer.Get(), "BackBuffer[0]");

	backBuffer.Reset();

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = mClientWidth;
	depthStencilDesc.Height = mClientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if (mEnable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	HRD(pDevice->CreateTexture2D(&depthStencilDesc, nullptr, pDepthStencilBuffer.GetAddressOf()));
	HRD(pDevice->CreateDepthStencilView(pDepthStencilBuffer.Get(), nullptr, pDepthStencilView.GetAddressOf()));

	pContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), pDepthStencilView.Get());

	mViewport.TopLeftX = 0;
	mViewport.TopLeftY = 0;
	mViewport.Width = static_cast<float>(mClientWidth);
	mViewport.Height = static_cast<float>(mClientHeight);
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;

	pContext->RSSetViewports(1, &mViewport);

	D3D11SetDebugObjectName(pDepthStencilBuffer.Get(), "DepthStencilBuffer");
	D3D11SetDebugObjectName(pDepthStencilView.Get(), "DepthStencilView");
	D3D11SetDebugObjectName(pRenderTargetView.Get(), "BackBufferRTV[0]");
}

void Graphics::ReleaseResource()
{
	assert(pd2dFactory);
	assert(pd2dFactory);
	pColorBrush.Reset();
	pd2dRenderTarget.Reset();

	assert(pContext);
	assert(pDevice);
	assert(pSwapChain);

	if (pDevice1 != nullptr)
	{
		assert(pContext1);
		assert(pDevice1);
		assert(pSwapChain1);
	}

	pRenderTargetView.Reset();
	pDepthStencilView.Reset();
	pDepthStencilBuffer.Reset();
}

void Graphics::ClearUp()
{
	pContext->ClearState();
}

void Graphics::ShiftShowMode(D3D11_FILL_MODE mode = D3D11_FILL_SOLID)
{
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
	rd.FillMode = mode;
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = false;
	rd.DepthClipEnable = true;
	pDevice->CreateRasterizerState(&rd, pRasterizerState.GetAddressOf());
	pContext->RSSetState(pRasterizerState.Get());
}

void Graphics::CleanFrame()
{
	const float color[4]{ 0, 0, 0, 1 };
	pContext->ClearRenderTargetView(pRenderTargetView.Get(), color);
	pContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Graphics::EndFrame()
{
	pSwapChain->Present(0,0);
}

void Graphics::onUdpate(float deltaTime)
{
	mRenderCamera.get()->onUpdate(deltaTime);
}

void Graphics::DrawIndexed(UINT mCount) noexcept
{
	pContext->DrawIndexed(mCount, 0u, 0u);
}

void Graphics::setShowText(const std::wstring & str, float leftTopX, float leftTopY, float width, float height, bool canShow)
{
	mCanShowText = canShow;
	if (mCanShowText != true)
	{
		return;
	}
	mTextDisplay.str = str;
	mTextDisplay.leftTopX = leftTopX;
	mTextDisplay.leftTopY = leftTopY;
	mTextDisplay.width = width;
	mTextDisplay.height = height;
}

void Graphics::showText()
{
	if (mCanShowText != true)
	{
		return;
	}
	pd2dRenderTarget->BeginDraw();

	D2D1_RECT_F rc{ mTextDisplay.leftTopX,mTextDisplay.leftTopY,mTextDisplay.width,mTextDisplay.height };
	pd2dRenderTarget->DrawTextW(mTextDisplay.str.c_str(), mTextDisplay.str.size() + 1, pTextFormat.Get(), rc, pColorBrush.Get());

	pd2dRenderTarget->EndDraw();
}

DirectX::XMMATRIX Graphics::GetViewProj() const noexcept
{
	return mRenderCamera.get()->getViewProjXM();
}

//DirectX::XMVECTOR Graphics::getcamForward()
//{
//	return mRenderCamera.get()->getForward();
//}
//
//DirectX::XMVECTOR Graphics::getcamRight()
//{
//	return mRenderCamera.get()->getRight();
//}
//
//DirectX::XMVECTOR Graphics::getcamUp()
//{
//	return  mRenderCamera.get()->getUp();
//}
//
//DirectX::XMVECTOR Graphics::getCamPos()
//{
//	return mRenderCamera.get()->getPosition();
//}
