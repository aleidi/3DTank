#include "Mesh.h"
#include "RenderComponent.h"

Mesh::Mesh(RenderComponent * owner)
	:mOwner(owner), mIsTransparent(false)
{
	enableDraw(true);
}

void Mesh::onUpdate(float deltaTime) noexcept
{
}

DirectX::XMMATRIX Mesh::getTransformXM() const noexcept
{
	return mOwner->getWorldMatrix();
}

Material Mesh::getMaterial() const noexcept
{
	return mOwner->getMaterial();
}

void Mesh::setTransparent(bool value) noexcept
{
	mIsTransparent = value;
}

bool Mesh::isTransparent() const noexcept
{
	return mIsTransparent;
}

Mesh::~Mesh()
{
	if (mOwner != nullptr)
	{
		mOwner = nullptr;
	}
}