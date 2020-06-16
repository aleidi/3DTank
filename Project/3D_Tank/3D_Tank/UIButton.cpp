#include "UIButton.h"
#include "bindableBase.h"

UIButton::UIButton(Graphics& gfx)
	:UIButton(gfx,L"")
{
}

UIButton::UIButton(Graphics & gfx, const std::wstring & texPath)
{
	mWidth = 100.0f;
	mHeight = 100.0f;
	mX = 0.0f;
	mY = 0.0f;

	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getUIPanel(mesh);

	addBind(std::make_unique<VertexBuffer>(gfx, mesh.vertices, true));

	auto pvs = std::make_unique<VertexShader>(gfx, L"UIVertexShader.cso");
	auto pvsbc = pvs->getBytecode();
	addBind(std::move(pvs));

	addBind(std::make_unique<PixelShader>(gfx, L"UIPSButton.cso"));

	addIndexBuffer(std::make_unique<IndexBuffer>(gfx, mesh.indices));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	addBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	addBind(std::make_unique<Texture>(gfx, texPath));

	addBind(std::make_unique<Sampler>(gfx));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_unique<UITransformCbuf>(gfx, *this));

	mMaterial.Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mColors[0] = mMaterial.Color;
	mPCBuf = std::make_unique<PixelConstantBuffer<XMFLOAT4>>(gfx, mMaterial.Color);
}

void UIButton::draw(Graphics& gfx) const noexcept
{
	mPCBuf->onUpdate(gfx, mMaterial.Color);

	for (auto& b : mBinds)
	{
		b->bind(gfx);
	}
	mPCBuf->bind(gfx);
	gfx.DrawIndexed(pIndexBuffer->getCount());
}

void UIButton::checkState(float x, float y, bool isPressed)
{
	y = WINDOW_HEIGHT - y;
	switch (mBtnState)
	{
	case State::Normal:
		if (x > mX && x < mX + mWidth && y > mY && y < mY + mHeight)
		{
			mBtnState = State::Selected;
			break;
		}
		onNormal();
		break;

	case State::Selected:
		if (true == isPressed)
		{
			mBtnState = State::Pressed;
			break;
		}
		if (x < mX || x > mX + mWidth || y < mY || y > mY + mHeight)
		{
			mBtnState = Normal;
			break;
		}
		onSelected();
		break;

	case State::Pressed:
		if (false == isPressed)
		{
			mBtnState = State::Selected;
			break;
		}
		onPressed();
		break;
	}
}

void UIButton::onNormal()
{
	mMaterial.Color = mColors[0];
}

void UIButton::onSelected()
{
	mMaterial.Color = mColors[1];
}

void UIButton::onPressed()
{
	mMaterial.Color = mColors[2];
}

void UIButton::setColor(XMFLOAT4 color, State btnState)
{
	switch (btnState)
	{
	case State::Normal:
		mColors[0] = color;
		break;
	case State::Selected:
		mColors[1] = color;
		break;
	case State::Pressed:
		mColors[2] = color;
	}
}
