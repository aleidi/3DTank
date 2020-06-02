#include "Mesh.h"
#include "RenderComponent.h"

Mesh::Mesh(RenderComponent * owner, Graphics& gfx)
	:mOwner(owner)
{
}

void Mesh::Update(float deltaTime) noexcept
{
}

DirectX::XMMATRIX Mesh::GetTransformXM() const noexcept
{
	return DirectX::XMMATRIX();
}

Mesh::~Mesh()
{
	if (mOwner != nullptr)
	{
		delete mOwner;
		mOwner = nullptr;
	}
}