#include "Bindable.h"

ID3D11DeviceContext* Bindable::GetContext(Graphics& gfx) noexcept
{
	return gfx.GetContext();
}

ID3D11Device* Bindable::getDevice(Graphics& gfx) noexcept
{
	return gfx.getDevice();
}