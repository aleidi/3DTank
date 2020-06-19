#include "Bindable.h"

ID3D11DeviceContext* Bindable::getContext(Graphics& gfx) noexcept
{
	return gfx.getContext();
}

ID3D11Device* Bindable::getDevice(Graphics& gfx) noexcept
{
	return gfx.getDevice();
}