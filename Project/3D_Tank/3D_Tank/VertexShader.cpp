#include "VertexShader.h"
#include <string>

VertexShader::VertexShader(Graphics& gfx, const std::wstring& path)
{
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vs;
	const HRESULT hrLoad = D3DReadFileToBlob(path.c_str(), &pBytecodeBlob);
	if (FAILED(hrLoad) || pBytecodeBlob == nullptr)
	{
		std::wstring msg = L"Failed to load vertex shader: " + path;
		MessageBoxW(nullptr, msg.c_str(), L"Shader Load Error", MB_OK | MB_ICONERROR);
		return;
	}

	const HRESULT hrCreate = getDevice(gfx)->CreateVertexShader(
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		nullptr,
		&vs);
	if (FAILED(hrCreate))
	{
		std::wstring msg = L"Failed to create vertex shader: " + path;
		MessageBoxW(nullptr, msg.c_str(), L"Shader Create Error", MB_OK | MB_ICONERROR);
		return;
	}

	pVertexShader.push_back(vs);
}

VertexShader::VertexShader(Graphics& gfx, std::vector<std::wstring>& pathes)
{
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vs;
	for (std::vector<std::wstring>::iterator it = pathes.begin(); it != pathes.end(); ++it)
	{
		const HRESULT hrLoad = D3DReadFileToBlob(it->c_str(), &pBytecodeBlob);
		if (FAILED(hrLoad) || pBytecodeBlob == nullptr)
		{
			std::wstring msg = L"Failed to load vertex shader: " + *it;
			MessageBoxW(nullptr, msg.c_str(), L"Shader Load Error", MB_OK | MB_ICONERROR);
			continue;
		}

		const HRESULT hrCreate = getDevice(gfx)->CreateVertexShader(
			pBytecodeBlob->GetBufferPointer(),
			pBytecodeBlob->GetBufferSize(),
			nullptr,
			&vs);
		if (FAILED(hrCreate))
		{
			std::wstring msg = L"Failed to create vertex shader: " + *it;
			MessageBoxW(nullptr, msg.c_str(), L"Shader Create Error", MB_OK | MB_ICONERROR);
			continue;
		}

		pVertexShader.push_back(vs);
	}
}

void VertexShader::bind(Graphics& gfx) noexcept
{
	getContext(gfx)->VSSetShader(pVertexShader[mCurrentShader].Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::getBytecode() const noexcept
{
	return pBytecodeBlob.Get();
}

void VertexShader::changeShader(int index) noexcept
{
	mCurrentShader = index;
}
