#include "Mesh.h"
#include "RenderComponent.h"

Mesh::Mesh(RenderComponent * owner)
	:mOwner(owner)
{
}

void Mesh::onUpdate(float deltaTime) noexcept
{
}

DirectX::XMMATRIX Mesh::getTransformXM() const noexcept
{
	return mOwner->getWorldMatrix();
}

Mesh::~Mesh()
{
	if (mOwner != nullptr)
	{
		delete mOwner;
		mOwner = nullptr;
	}
}