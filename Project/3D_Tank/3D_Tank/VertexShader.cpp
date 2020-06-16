#include "VertexShader.h"

VertexShader::VertexShader(Graphics& gfx, const std::wstring& path)
{
	Microsoft::WRL::ComPtr<ID3D11VertexShader>  vs;
	D3DReadFileToBlob(path.c_str(), &pBytecodeBlob);
	getDevice(gfx)->CreateVertexShader(
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		nullptr,
		&vs
	);
	pVertexShader.push_back(vs);
}

VertexShader::VertexShader(Graphics & gfx, std::vector<std::wstring>& pathes)
{
	Microsoft::WRL::ComPtr<ID3D11VertexShader>  vs;
	for (std::vector<std::wstring>::iterator it = pathes.begin(); it != pathes.end(); ++it)
	{
		D3DReadFileToBlob(it->c_str(), &pBytecodeBlob);
		getDevice(gfx)->CreateVertexShader(
			pBytecodeBlob->GetBufferPointer(),
			pBytecodeBlob->GetBufferSize(),
			nullptr,
			&vs
		);
		pVertexShader.push_back(vs);
	}
}

void VertexShader::bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->VSSetShader(pVertexShader[mCurrentShader].Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::getBytecode() const noexcept
{
	return pBytecodeBlob.Get();
}

void VertexShader::changeShader(int index) noexcept
{
	mCurrentShader = index;
}
