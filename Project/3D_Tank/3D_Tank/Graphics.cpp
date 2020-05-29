#include <cassert>
#include <math.h>
#include <d3dcompiler.h>
#include "dxgi1_2.h"
#include "dxgi.h"
#include "Window.h"
#include "Graphics.h"
#include "RenderCamera.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

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

Graphics::Graphics(Window& wnd)
	:
	mhMainWnd(wnd.getHwnd()),mClientWidth(WINDOW_WIDTH),mClientHeight(WINDOW_HEIGHT),
	mRenderCamera(std::make_unique<RenderCamera>(this))
{
	DXGI_SWAP_CHAIN_DESC sd;

	sd.BufferDesc.Width = mClientWidth; 
	sd.BufferDesc.Height = mClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = mhMainWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr, 0,
		nullptr, 0,
		D3D11_SDK_VERSION,
		&sd, pSwapChain.GetAddressOf(),
		pDevice.GetAddressOf(),
		nullptr,
		pContext.GetAddressOf());

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

	pDevice->CreateTexture2D(&depthStencilDesc, 0, depthStencilBuffer.GetAddressOf());
	pDevice->CreateDepthStencilView(depthStencilBuffer.Get(), 0, depthStencilView.GetAddressOf());

	pContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), depthStencilView.Get());

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = false;
	rd.DepthClipEnable = true;
	pDevice->CreateRasterizerState(&rd, pRasterizerState.GetAddressOf());
	pContext->RSSetState(pRasterizerState.Get());

	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = static_cast<float>(mClientWidth);
	vp.Height = static_cast<float>(mClientHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	pContext->RSSetViewports(1, &vp);
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
	pContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Graphics::EndFrame()
{
	pSwapChain->Present(0,0);
}

void Graphics::DrawIndexed(UINT mCount) noexcept
{
	pContext->DrawIndexed(mCount, 0u, 0u);
}

DirectX::XMMATRIX Graphics::GetViewProj() const noexcept
{
	return mRenderCamera.get()->getViewProjXM();
}

void Graphics::CamSetPosition(float x, float y, float z)
{
	mRenderCamera.get()->setPosition(x, y, z);
}

void Graphics::CamSetRotation(float x, float y, float z)
{
	mRenderCamera.get()->setRotation(x, y, z);
}
