#include "Graphics.h"
#include <cassert>
#include <math.h>
#include <d3dcompiler.h>
#include "dxgi1_2.h"
#include "dxgi.h"
#include "Window.h"

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
	mhMainWnd(wnd.getHwnd()),mClientWidth(WINDOW_WIDTH),mClientHeight(WINDOW_HEIGHT)
{
	//描述交换链
	DXGI_SWAP_CHAIN_DESC sd; //交换链描述结构体，描述所要创建交换链的特性
	//BufferDesc 描述了后台缓冲区的属性
	sd.BufferDesc.Width = mClientWidth; //窗口客户区宽度
	sd.BufferDesc.Height = mClientHeight; //窗口客户区高度
	sd.BufferDesc.RefreshRate.Numerator = 60; //刷新率分子
	sd.BufferDesc.RefreshRate.Denominator = 1; //刷新率分母
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //后台缓冲区的用途，这里用作渲染目标
	sd.BufferCount = 1; //后台缓冲区的数量，这里用一个后台缓冲实现双缓冲
	sd.OutputWindow = mhMainWnd; //目标窗口句柄
	sd.Windowed = true; //程序以窗口模式运行
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //让显卡驱动程序选择最高效的显示模式
	sd.Flags = 0; //窗口切换全拼模式时，D3D使用当前的桌面显示模式

	//创设备和交换链
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

	// Step 2. 为后台缓冲与深度缓冲创建视图,将视图绑定至管线的输出合并阶段

	//创建渲染目标视图
	ID3D11Texture2D* pBackBuffer;
	//GetBuffer()用于获取一个交换链的后台缓冲区指针
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView(pBackBuffer, 0, pRenderTargetView.GetAddressOf());
	pBackBuffer->Release();

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = mClientWidth; //纹理的宽度
	depthStencilDesc.Height = mClientWidth; //纹理的高度
	depthStencilDesc.MipLevels = 1; //多级渐进纹理的数量
	depthStencilDesc.ArraySize = 1; //纹理数组中的纹理数量
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT; //表示GPU对资源执行读写操作，CPU不能读写该资源
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; //将纹理作为深度缓冲绑定到管线上
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	pDevice->CreateTexture2D(&depthStencilDesc, 0, depthStencilBuffer.GetAddressOf());
	pDevice->CreateDepthStencilView(depthStencilBuffer.Get(), 0, depthStencilView.GetAddressOf());

	//将视图绑定至输出合并阶段
	pContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), depthStencilView.Get());

	//设置光栅化配置
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = false;
	rd.DepthClipEnable = true;
	pDevice->CreateRasterizerState(&rd, pRasterizerState.GetAddressOf());
	pContext->RSSetState(pRasterizerState.Get());

	//设置视口
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = static_cast<float>(mClientWidth);
	vp.Height = static_cast<float>(mClientHeight);
	vp.MinDepth = 0.0f; //表示深度缓冲区的最小值
	vp.MaxDepth = 1.0f; //表示深度缓冲区的最大值

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

void Graphics::DrawIndexed(UINT count) noexcept
{
	pContext->DrawIndexed(count, 0u, 0u);
}

void Graphics::SetProjection(DirectX::FXMMATRIX proj) noexcept
{
	projection = proj;
}

DirectX::XMMATRIX Graphics::GetProjection() const noexcept
{
	return projection;
}