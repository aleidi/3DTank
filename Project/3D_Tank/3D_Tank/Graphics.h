#pragma once
#include "EngineCommon.h"
#include <d3d11.h>
#include <d3d11_1.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <random>

class Window;
class RenderCamera;
class SkyBox;

using namespace DirectX;

class Graphics
{
	friend class Bindable;
	friend class RenderCamera;
public:

	struct TextDisplay 
	{
		TextDisplay()
		{
			str = L"";
			leftTopX = 0.0f;
			leftTopY = 0.0f;
			width = 0.0f;
			height = 0.0f;
		}
		std::wstring str;
		float leftTopX;
		float leftTopY;
		float width;
		float height;
	};

	Graphics(const Window& wnd);
	~Graphics();

	ID3D11Device* getDevice() const;
	ID3D11DeviceContext* getContext() const;
	bool InitD3D();
	bool InitD2D();
	void BindD2DResource();
	void BindD3DResource();
	void ReleaseResource();
	void ClearUp();
	void ShiftShowMode(D3D11_FILL_MODE mode);
	void CleanFrame();
	void EndFrame();
	void onUdpate(float deltaTime);
	void DrawSkyBox();

	void DrawIndexed(UINT mCount) noexcept;
	void setShowText(const std::wstring& str, float leftTopX, float leftTopY, float width, float height,bool canShow);
	void showText();
	DirectX::XMMATRIX getViewProj() const noexcept;
	DirectX::XMMATRIX getView() const noexcept;
	DirectX::XMMATRIX getProj() const noexcept;
	DirectX::XMVECTOR getCameraPosition() const noexcept;

	//test code
	//DirectX::XMVECTOR getcamForward();
	//DirectX::XMVECTOR getcamRight();
	//DirectX::XMVECTOR getcamUp();
	//DirectX::XMVECTOR getCamPos();


private:
	int mClientWidth;
	int mClientHeight;
	HWND mhMainWnd;

	TextDisplay mTextDisplay;
	bool mCanShowText;
	DirectX::XMMATRIX mProjection;

	D3D_DRIVER_TYPE mDriverType;
	D3D_FEATURE_LEVEL mFeatureLevel;
	UINT m4xMsaaQuality;
	bool mEnable4xMsaa;
	D3D11_VIEWPORT mViewport;

	// Direct3D 11
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	// Direct3D 11.1
	Microsoft::WRL::ComPtr<ID3D11Device1> pDevice1;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> pContext1;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> pSwapChain1;
	//Direct2D
	Microsoft::WRL::ComPtr<ID2D1Factory> pd2dFactory;
	Microsoft::WRL::ComPtr<ID2D1RenderTarget> pd2dRenderTarget;
	//DWrite
	Microsoft::WRL::ComPtr<IDWriteFactory> pWriteFactory;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pColorBrush;
	Microsoft::WRL::ComPtr<IDWriteTextFormat> pTextFormat;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> pRasterizerState;

	std::unique_ptr<RenderCamera> mRenderCamera;
	std::unique_ptr<SkyBox> mSkyBox;
};