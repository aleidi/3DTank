#include "PixelShader.h"
#include <string>

PixelShader::PixelShader(Graphics& gfx, const std::wstring& path)
{
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	const HRESULT hrLoad = D3DReadFileToBlob(path.c_str(), &pBlob);
	if (FAILED(hrLoad) || pBlob == nullptr)
	{
		std::wstring msg = L"Failed to load pixel shader: " + path;
		MessageBoxW(nullptr, msg.c_str(), L"Shader Load Error", MB_OK | MB_ICONERROR);
		return;
	}

	const HRESULT hrCreate = getDevice(gfx)->CreatePixelShader(
		pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	if (FAILED(hrCreate))
	{
		std::wstring msg = L"Failed to create pixel shader: " + path;
		MessageBoxW(nullptr, msg.c_str(), L"Shader Create Error", MB_OK | MB_ICONERROR);
	}
}

void PixelShader::bind(Graphics& gfx) noexcept
{
	getContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}