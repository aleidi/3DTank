#include "UIText3D.h"

UIText3D::UIText3D(Graphics& gfx)
 	:UIText3D(gfx, L"未设置文本")
{
}

UIText3D::UIText3D(Graphics& gfx, std::wstring text)
	:mInterval(0.06f),mSizeFactorX(1.0f),mSizeFactorY(1.0f)
{
	mText = text;

	mX = 0.0f;
	mY = 0.0f;
	mZ = 0.0;
	mWidth = 0.05f;
	mHeight = 0.05f;
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

	//int index = 0;
	//FreeType ft(gfx);
	//for (std::wstring::iterator it = mText.begin(); it != mText.end(); ++it)
	//{
	//	FreeType::Character charInfo;
	//	charInfo = ft.getChar(gfx, *it);
	//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
	//	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	//	srvDesc.Format = DXGI_FORMAT_R8_UNORM;
	//	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	//	srvDesc.Texture2D.MipLevels = 1;
	//	srvDesc.Texture2D.MostDetailedMip = 0;
	//	gfx.getDevice()->CreateShaderResourceView(charInfo.Texture.Get(), &srvDesc, srv.GetAddressOf());
	//	pSRVs.push_back(srv);
	//	mChars.push_back(charInfo);
	//	++index;
	//}

	addBind(std::make_unique<Sampler>(gfx));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_unique<TransferCbuf>(gfx, *this));

	//addBind(std::make_unique<UITransformCbuf>(gfx, *this));

	mMaterial.Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mPCBuf = std::make_unique<PixelConstantBuffer<DirectX::XMFLOAT4>>(gfx, mMaterial.Color);

	addBind(std::make_unique<GeometryShader>());

	mText2D = new UIText(gfx, mText);
	initRenderTarget(gfx);
	renderTarget(gfx);
}

DirectX::XMMATRIX UIText3D::getTransformXM() const noexcept
{
	return DirectX::XMMatrixScaling(mWidth*mSizeFactorX,mHeight*mSizeFactorY,0.0f)*
		DirectX::XMMatrixRotationRollPitchYaw(mPitch, mYaw, mRoll)*
		DirectX::XMMatrixTranslation(mX, mY, mZ);
}

void UIText3D::draw(Graphics& gfx) noexcept
{
	if (mIsEnable != true)
	{
		return;
	}

	renderTarget(gfx);

	XMFLOAT3 camPos;
	DirectX::XMStoreFloat3(&camPos,gfx.getCameraPosition());
	// Calculate the rotation that needs to be applied to the billboard model to face the current camera position using the arc tangent function.
	mYaw = atan2(mX - camPos.x, mZ - camPos.z);

	mPCBuf->onUpdate(gfx, mMaterial.Color);
	mPCBuf->bind(gfx);
	setBlendTransparent(gfx);
	gfx.getContext()->PSSetShaderResources(0, 1, pSRVRT.GetAddressOf());
	for (auto& b : mBinds)
	{
		b->bind(gfx);
	}
	gfx.DrawIndexed(pIndexBuffer->getCount());

	resetBlendState(gfx);
}

//void UIText3D::draw(Graphics& gfx) noexcept
//{
//	if (mIsEnable != true)
//	{
//		return;
//	}
//
//	mPCBuf->onUpdate(gfx, mMaterial.Color);
//	mPCBuf->bind(gfx);
//	setBlendTransparent(gfx);
//
//	int index = 0;
//	float storeX = (float)mX;
//	float x = (float)mX;
//	for (std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>::iterator it = pSRVs.begin();
//		it != pSRVs.end(); ++it)
//	{
//		mX = x;
//		gfx.getContext()->PSSetShaderResources(0, 1, it->GetAddressOf());
//		for (auto& b : mBinds)
//		{
//			b->bind(gfx);
//		}
//		gfx.DrawIndexed(pIndexBuffer->getCount());
//		x += mInterval*mSizeFactorX;
//		++index;
//	}
//	mX = storeX;
//	resetBlendState(gfx);
//}

void UIText3D::setInterval(float value)
{
	mInterval = value;
}

void UIText3D::setSizeScale(float x, float y)
{
	mSizeFactorX = x;
	mSizeFactorY = y;
}

void UIText3D::renderTarget(Graphics & gfx)
{
	int count{ 0 };
	for (std::wstring::iterator it = mText.begin(); it != mText.end(); ++it)
	{
		++count;
	}


	gfx.getContext()->OMGetRenderTargets(1, pRTCashe.GetAddressOf(), pDSVCashe.GetAddressOf());

	gfx.getContext()->OMSetRenderTargets(1, pRenderTargetViewMap.GetAddressOf(), pDSVCashe.Get());

	float color[4]{ 0, 0, 0, 1 };
	gfx.getContext()->ClearRenderTargetView(pRenderTargetViewMap.Get(), color);

	mText2D->setText(mText);
	mText2D->draw(gfx);

	gfx.getContext()->OMSetRenderTargets(1, pRTCashe.GetAddressOf(), pDSVCashe.Get());
}

void UIText3D::initRenderTarget(Graphics & gfx)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = WINDOW_WIDTH;
	textureDesc.Height = WINDOW_HEIGHT;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;


	gfx.getDevice()->CreateTexture2D(&textureDesc, NULL, pRenderTargetTextureMap.GetAddressOf());

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	gfx.getDevice()->CreateRenderTargetView(pRenderTargetTextureMap.Get(), &renderTargetViewDesc, pRenderTargetViewMap.GetAddressOf());

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	gfx.getDevice()->CreateShaderResourceView(pRenderTargetTextureMap.Get(), &shaderResourceViewDesc, pSRVRT.GetAddressOf());

	mText2D->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0.0f);
}
