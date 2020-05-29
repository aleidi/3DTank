#pragma once
#include "Drawable.h"
#include "EngineCommon.h"

class Drawable3D : public Drawable
{
public:
	Drawable3D() = default;
	Drawable3D(const Drawable3D&) = delete;
	virtual DirectX::XMMATRIX GetTransformXM() const noexcept { return DirectX::XMMATRIX();}
	void setID(UINT id) noexcept { mID = id; }
	UINT getID() noexcept { return mID; }
protected:
	UINT mID;
};

