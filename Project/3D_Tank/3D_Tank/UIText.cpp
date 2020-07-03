#include "UIText.h"
#include "RenderManager.h"

UIText::UIText(Graphics& gfx)
	:UIText(gfx, L"未设置文本")
{
}

UIText::UIText(Graphics& gfx, std::wstring text)
	:mText(text)
{
	mX =  WINDOW_WIDTH /2;
	mY = WINDOW_HEIGHT /2;
	setEnable(true);

	GeometryGenerator::Mesh mesh;
	GeometryGenerator::getUIText(mesh);

	addBind(std::make_unique<VertexBuffer>(gfx, mesh.vertices));

	auto pvs = std::make_unique<VertexShader>(gfx, L"UIVertexShader.cso");
	auto pvsbc = pvs->getBytecode();
	addBind(std::move(pvs));

	addBind(std::make_unique<PixelShader>(gfx, L"UIPSText.cso"));

	addIndexBuffer(std::make_unique<IndexBuffer>(gfx, mesh.indices));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	addBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	FreeType ft(gfx);
	for (std::wstring::iterator it = mText.begin(); it != mText.end(); ++it)
	{
		FreeType::Character charInfo;
		charInfo = ft.getChar(gfx, *it);
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_R8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;
		gfx.getDevice()->CreateShaderResourceView(charInfo.Texture.Get(), &srvDesc, srv.GetAddressOf());
		pSRVs.push_back(srv);
		mChars.push_back(charInfo);
	}

	addBind(std::make_unique<Sampler>(gfx));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_unique<UITransformCbuf>(gfx, *this));

	mMaterial.Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mPCBuf = std::make_unique<PixelConstantBuffer<DirectX::XMFLOAT4>>(gfx, mMaterial.Color);

	addBind(std::make_unique<GeometryShader>());

}

void UIText::draw(Graphics& gfx) noexcept
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
		mY = y - (mChars[index].SizeY - mChars[index].BearingY);
		mWidth = mChars[index].SizeX;
		mHeight = mChars[index].SizeY;
		gfx.getContext()->PSSetShaderResources(0, 1, it->GetAddressOf());
		for (auto& b : mBinds)
		{
			b->bind(gfx);
		}
		gfx.DrawIndexed(pIndexBuffer->getCount());
		x += (mChars[index].Advance >> 6);
		++index;
	}
	mX = storeX;
	mY = y;
	resetBlendState(gfx);
}

void UIText::setText(const std::wstring& wstr)
{
	Graphics& gfx = RenderManager::sGetInstance()->getGraphics();
	pSRVs.clear();
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>().swap(pSRVs);
	mChars.clear();
	std::vector<FreeType::Character>().swap(mChars);
	mText = wstr;

	FreeType ft(gfx);
	for (std::wstring::iterator it = mText.begin(); it != mText.end(); ++it)
	{
		FreeType::Character charInfo;
		charInfo = ft.getChar(gfx, *it);
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_R8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;
		gfx.getDevice()->CreateShaderResourceView(charInfo.Texture.Get(), &srvDesc, srv.GetAddressOf());
		pSRVs.push_back(srv);
		mChars.push_back(charInfo);
	}
}
