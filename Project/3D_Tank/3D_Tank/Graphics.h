#pragma once
#include "EngineCommon.h"
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>

class Window;
class RenderCamera;

using namespace DirectX;

class Graphics
{
	friend class Bindable;
	friend class RenderCamera;
public:
	Graphics(const Window& wnd);
	~Graphics();

	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetContext() const;
	void ClearUp();
	void ShiftShowMode(D3D11_FILL_MODE mode);
	void CleanFrame();
	void EndFrame();

	void DrawIndexed(UINT mCount) noexcept;
	DirectX::XMMATRIX GetViewProj() const noexcept;

	//test code
	void CamSetPosition(float x, float y, float z);
	void CamSetRotation(float x, float y, float z);

private:
	int mClientWidth;
	int mClientHeight;
	HWND mhMainWnd;
	DirectX::XMMATRIX mProjection;

	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> pRasterizerState;

	std::unique_ptr<RenderCamera> mRenderCamera;
};