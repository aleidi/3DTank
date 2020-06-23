#include "GeometryShader.h"

GeometryShader::GeometryShader(Graphics& gfx, const std::wstring& path)
	:pGeometryShader(), mCurrentShader(0)
{
	Microsoft::WRL::ComPtr<ID3D11GeometryShader>  gs;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(path.c_str(), &pBlob);
	getDevice(gfx)->CreateGeometryShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, gs.GetAddressOf());
	pGeometryShader.push_back(gs);
}

GeometryShader::GeometryShader()
{
	pGeometryShader.push_back(nullptr);
}

GeometryShader::GeometryShader(Graphics& gfx, std::vector<std::wstring>& pathes)
{
	Microsoft::WRL::ComPtr<ID3D11GeometryShader>  gs;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	for (std::vector<std::wstring>::iterator it = pathes.begin(); it != pathes.end(); ++it)
	{
		D3DReadFileToBlob(it->c_str(), &pBlob);
		getDevice(gfx)->CreateGeometryShader(
			pBlob->GetBufferPointer(),
			pBlob->GetBufferSize(),
			nullptr,
			gs.GetAddressOf()
		);
		pGeometryShader.push_back(gs);
	}
}

void GeometryShader::bind(Graphics& gfx) noexcept
{
	getContext(gfx)->GSSetShader(pGeometryShader[mCurrentShader].Get(), nullptr, 0u);
}

void GeometryShader::changeShader(int index) noexcept
{
	mCurrentShader = index;
}
