#pragma once
#include "Bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(Graphics& gfx, const std::wstring& path);
	VertexShader(Graphics& gfx, std::vector<std::wstring>& pathes);
	void bind(Graphics& gfx) noexcept override;
	ID3DBlob* getBytecode() const noexcept;
	void changeShader(int index) noexcept;
protected:
	Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
	std::vector<Microsoft::WRL::ComPtr<ID3D11VertexShader>> pVertexShader;
	int mCurrentShader;
};