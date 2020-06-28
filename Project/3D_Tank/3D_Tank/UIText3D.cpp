#include "UIText3D.h"

UIText3D::UIText3D(Graphics& gfx)
 	:UIText3D(gfx, L"未设置文本")
{
}

UIText3D::UIText3D(Graphics& gfx, std::wstring text)
{
	mText = text;

	mX = 0.0f;
	mY = 0.0f;
	mZ = 0.0;
	mWidth = 2.0f;
	mHeight = 1.0f;
	setEnable(true);

	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getUIText(mesh);

	addBind(std::make_unique<VertexBuffer>(gfx, mesh.vertices));

	auto pvs = std::make_unique<VertexShader>(gfx, L"UIText3D_VS.cso");
	auto pvsbc = pvs->getBytecode();
	addBind(std::move(pvs));

	addBind(std::make_unique<PixelShader>(gfx, L"UIText3D_PS.cso"));

	addIndexBuffer(std::make_unique<IndexBuffer>(gfx, mesh.indices));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	addBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	int index = 0;
	FreeType ft(gfx);
	for (std::wstring::iterator it = mText.begin(); it != mText.end(); ++it)
	{
		FreeType::Character charInfo;
		charInfo = ft.getChar(gfx, mText.c_str() + index);
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_R8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;
		gfx.getDevice()->CreateShaderResourceView(charInfo.Texture.Get(), &srvDesc, srv.GetAddressOf());
		pSRVs.push_back(srv);
		mChars.push_back(charInfo);
		++index;
	}

	addBind(std::make_unique<Sampler>(gfx));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_unique<TransferCbuf>(gfx, *this));

	//addBind(std::make_unique<UITransformCbuf>(gfx, *this));

	mMaterial.Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mPCBuf = std::make_unique<PixelConstantBuffer<DirectX::XMFLOAT4>>(gfx, mMaterial.Color);

	addBind(std::make_unique<GeometryShader>());

}

DirectX::XMMATRIX UIText3D::getTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(mPitch, mYaw, mRoll)*
		DirectX::XMMatrixTranslation(mX, mY, mZ);
}

void UIText3D::draw(Graphics& gfx) noexcept
{
	if (mIsEnable != true)
	{
		return;
	}

	mPCBuf->onUpdate(gfx, mMaterial.Color);
	mPCBuf->bind(gfx);
	setBlendTransparent(gfx);

	int index = 0;
	int storeX = (int)mX;
	int x = (int)mX;
	int y = (int)mY;
	for (std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>::iterator it = pSRVs.begin();
		it != pSRVs.end(); ++it)
	{
		mX = x + mChars[index].BearingX;
		//mY = y - ((int)mChars[index].SizeY - (int)mChars[index].BearingY);
		mWidth = mChars[index].SizeX;
		mHeight = mChars[index].SizeY;
		gfx.getContext()->PSSetShaderResources(0, 1, it->GetAddressOf());
		for (auto& b : mBinds)
		{
			b->bind(gfx);
		}
		gfx.DrawIndexed(pIndexBuffer->getCount());
		x += mWidth / 28;
		++index;
	}
	mX = storeX;
	mY = y;
	resetBlendState(gfx);

}