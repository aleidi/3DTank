#pragma once
#include "Bindable.h"

class GeometryShader : public Bindable
{
public:
	GeometryShader(Graphics& gfx, const std::wstring& path);
	GeometryShader(Graphics& gfx, std::vector<std::wstring>& pathes);
	GeometryShader();
	void bind(Graphics& gfx) noexcept override;
	void changeShader(int index) noexcept;

private:
	std::vector<Microsoft::WRL::ComPtr<ID3D11GeometryShader>> pGeometryShader;
	int mCurrentShader;
};

