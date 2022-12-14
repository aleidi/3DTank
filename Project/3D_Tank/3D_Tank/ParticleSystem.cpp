#include "ParticleSystem.h"
#include "Engine.h"
#include <time.h>

ParticleSystem::ParticleSystem(Graphics& gfx, const std::wstring& texture, int maxParticles)
	:mMaxParticles(maxParticles),mLifeTime(1),mEmitRate(2), mNeedParticles(mLifeTime * mEmitRate), mStepTime(0.0f),
	mDuration(0.0f), mTimeCount(0.0f), mIsLoop(false),
	mMaxSpeed(1.0f),mMinSpeed(1.0f), mStartVelocity(XMFLOAT3(0.0f, 1.0f, 0.0f)),
	 mMaxTileX(1.0f),mMaxTileY(1.0f),mTileInterval(0.1f),mTileStepX(1.0f),mTileStepY(1),
	mPosition(XMFLOAT3(0.0f, 0.0f, 5.0f)),mRotation(XMFLOAT3(0.0f, 0.0f, 0.0f)),mScale(XMFLOAT3(1.0f, 1.0f, 1.0f)),
	mStartRotation(XMFLOAT3(0.0f, 0.0f, 0.0f)),mStartScale(XMFLOAT3(1.0f, 1.0f, 1.0f)),mIsActivate(false)
{
	mEmitter = Emitter::NoEmit;

	std::vector<VertexPosSize> vertices;
	for (int i = 0; i < mMaxParticles; ++i)
	{
		VertexPosSize v;
		v.Size = XMFLOAT2(1.0f, 1.0f);
		vertices.push_back(v);
	}
	mVB = std::make_unique<VertexBuffer>(gfx, vertices, true);

	auto pvs = std::make_unique<VertexShader>(gfx, L"Particle_VS.cso");
	auto pvsbc = pvs->getBytecode();
	addBind(std::move(pvs));

	addBind(std::make_unique<GeometryShader>(gfx, L"Particle_GS.cso"));

	addBind(std::make_unique<PixelShader>(gfx, L"Particle_PS.cso"));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "SIZE",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	addBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	addBind(std::make_unique<Texture>(gfx, texture.c_str()));

	addBind(std::make_unique<Sampler>(gfx));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_POINTLIST));

	mMaterial.Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mPCBuf = std::make_unique<PixelConstantBuffer<XMFLOAT4>>(gfx, mMaterial.Color);

	CBGS cbgs;
	mGSCBuf = std::make_unique<GeometryConstantBuffer<CBGS>>(gfx, cbgs);

	addBind(std::make_unique<Rasterizer>(gfx));

}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::onUpdate(float deltaTime) noexcept
{
}

DirectX::XMMATRIX ParticleSystem::getTransformXM() const noexcept
{
	return XMMATRIX();
}

void ParticleSystem::setMaxPatricles(int value) noexcept
{
	mMaxParticles = value;

	mVB.reset();
	std::vector<VertexPosSize> vertices;
	for (int i = 0; i < mMaxParticles; ++i)
	{
		VertexPosSize v;
		v.Size = XMFLOAT2(1.0f, 1.0f);
		vertices.push_back(v);
	}
	mVB = std::make_unique<VertexBuffer>(RenderManager::sGetInstance()->getGraphics(), vertices, true);
}

void ParticleSystem::updateParticle(Graphics& gfx, float deltaTime, int& deathPatricles) noexcept
{
	deathPatricles = 0;
	for (std::vector<PAttribute>::iterator it = mParticles.begin(); it != mParticles.end(); ++it)
	{
		if (it->IsAlive)
		{
			it->AliveTime += deltaTime;
			if (it->AliveTime > mLifeTime)
			{
				it->IsAlive = false;
			}
			XMVECTOR pos, vel, step;
			pos = XMLoadFloat3(&it->Position);
			vel = XMLoadFloat3(&it->Velocity);
			step = XMVectorSet(deltaTime, deltaTime, deltaTime, 0.0f);
			XMStoreFloat3(&it->Position, DirectX::XMVectorMultiplyAdd(vel, step, pos));
			updateSprite(&(*it), deltaTime);
		}
		else
		{
			if (!mIsActivate)
			{
				++deathPatricles;
				continue;
			}
			resetParticle(&(*it));
		}
	}

}

void ParticleSystem::calculateNeedParticle()
{
	mNeedParticles = ceilf((float)mEmitRate * mLifeTime);
}

void ParticleSystem::draw(Graphics& gfx, float deltaTime) noexcept
{
	int count = 0;
	updateParticle(gfx, deltaTime, count);

	if (mIsActivate == true && mIsLoop != true)
	{
		mTimeCount += deltaTime;
		if (mTimeCount > mDuration)
		{
			mTimeCount = 0.0f;
			mIsActivate = false;
			return;
		}
	}
	if (mIsActivate != true && count == mParticles.size())
	{
		return;
	}

	if (mParticles.size() != mMaxParticles)
	{
		mStepTime += deltaTime;
	}
	float interval = 1.0f / (float)mEmitRate;
	if (mParticles.size() < mNeedParticles && mParticles.size() < mMaxParticles && mStepTime > interval)
	{
		PAttribute p;
		resetParticle(&p);
		mParticles.push_back(p);
		mStepTime = 0.0f;
	}
	D3D11_MAPPED_SUBRESOURCE msr;
	gfx.getContext()->Map(
		mVB->getBuffer(), 0u,
		D3D11_MAP_WRITE_DISCARD, 0u,
		&msr
	);
	VertexPosSize* vertices = reinterpret_cast<VertexPosSize*>(msr.pData);
	for (int i = 0; i < mParticles.size(); ++i)
	{
		vertices[i].Position = mParticles[i].Position;
		vertices[i].Size = XMFLOAT2(mParticles[i].Size.x, mParticles[i].Size.y);
		vertices[i].Tile.x = mParticles[i].Sprite.CurrentTileX;
		vertices[i].Tile.y = mParticles[i].Sprite.CurrentTileY;
		vertices[i].Tile.z = mMaxTileX;
		vertices[i].Tile.w = mMaxTileY;
	}
	gfx.getContext()->Unmap(mVB->getBuffer(), 0u);

	XMFLOAT3 cam;
	XMStoreFloat3(&cam, gfx.getCameraPosition());
	mGSCBuf->onUpdate(gfx,
		{
			XMMatrixTranspose(gfx.getView()),
			XMMatrixTranspose(gfx.getProj()),
			XMFLOAT3(cam.x,cam.y,cam.z),
		});

	mPCBuf->onUpdate(gfx, mMaterial.Color);

	setBlendTransparent(gfx);
	mVB->bind(gfx);
	mGSCBuf->bind(gfx);
	mPCBuf->bind(gfx);
	for (auto& b : mBinds)
	{
		b->bind(gfx);
	}
	gfx.DrawIndexed(4 * mParticles.size());

	resetBlendState(gfx);
}

void ParticleSystem::resetParticle(PAttribute* p)
{

	p->IsAlive = true;
	p->AliveTime = 0.0f;

	switch (mEmitter)
	{
	case Emitter::NoEmit:
		p->Position = mPosition;
		p->Rotation = mStartRotation;
		p->Size = mStartScale;
		p->Velocity = XMFLOAT3(0.0f,0.0f,0.0f);
		p->Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		p->Sprite.CurrentTileX = 0.0f;
		p->Sprite.CurrentTileY = 0.0f;
		p->Sprite.TileCount = 0.0f;
		break;
	case Emitter::Box:
		XMFLOAT3 pos = mPosition;
		float width = 10.0f * mScale.x;
		float depth = 10.0f * mScale.z;
		float height = 1.0f * mScale.y;

		pos.x += ((float)rand() / RAND_MAX * 2.0f - 1.0f)* width;
		pos.z += ((float)rand() / RAND_MAX * 2.0f - 1.0f)* depth;
		pos.y += ((float)rand() / RAND_MAX * 2.0f - 1.0f)* height;

		p->Position = pos;
		p->Rotation = mStartRotation;
		p->Size = mStartScale;
		mStartSpeed = ((float)rand() / RAND_MAX)*(mMaxSpeed - mMinSpeed) + mMinSpeed;
		XMFLOAT3 vel = mStartVelocity;
		vel.x *= mStartSpeed;
		vel.y *= mStartSpeed;
		vel.z *= mStartSpeed;
		p->Velocity = vel;
		p->Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		p->Sprite.CurrentTileX = 0.0f;
		p->Sprite.CurrentTileY = 0.0f;
		p->Sprite.TileCount = 0.0f;
		break;
	}
}

void ParticleSystem::setBlendTransparent(Graphics& gfx)
{
	Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState;
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	gfx.getDevice()->CreateBlendState(&bd, pBlendState.GetAddressOf());
	gfx.getContext()->OMSetBlendState(pBlendState.Get(), nullptr, 0xFFFFFFFF);
}

void ParticleSystem::resetBlendState(Graphics& gfx)
{
	Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState;
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.AlphaToCoverageEnable = true;
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	gfx.getDevice()->CreateBlendState(&bd, pBlendState.GetAddressOf());
	gfx.getContext()->OMSetBlendState(pBlendState.Get(), nullptr, 0xFFFFFFFF);
}

void ParticleSystem::updateSprite(PAttribute * p, float deltaTime)
{
	p->Sprite.TileCount += deltaTime;
	if (p->Sprite.TileCount >= mTileInterval)
	{
		p->Sprite.CurrentTileX += mTileStepX;
		if (p->Sprite.CurrentTileX >= mMaxTileX)
		{
			p->Sprite.CurrentTileY += mTileStepY;
			p->Sprite.CurrentTileX = 0.0f;
		}
		if (p->Sprite.CurrentTileY >= mMaxTileY)
		{
			p->Sprite.CurrentTileY = 0.0f;
		}
		p->Sprite.TileCount = 0.0f;
	}
}

void ParticleSystem::setEmitter(Emitter type)
{
	mEmitter = type;
}

void ParticleSystem::setLifeTime(float value)
{
	mLifeTime = value;
	calculateNeedParticle();
}

void ParticleSystem::setStartRotation(float x, float y, float z)
{
	mStartRotation.x = x;
	mStartRotation.y = y;
	mStartRotation.z = z;
}

void ParticleSystem::setStartScale(float x, float y, float z)
{
	mStartScale.x = x;
	mStartScale.y = y;
	mStartScale.z = z;
}

void ParticleSystem::setPosition(float x, float y, float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
	for (std::vector<PAttribute>::iterator it = mParticles.begin(); it != mParticles.end(); ++it)
	{
		resetParticle(&(*it));
	}
}

void ParticleSystem::setRange(float x, float y, float z)
{
	mScale.x = x;
	mScale.y = y;
	mScale.z = z;
}

void ParticleSystem::setMaxMinSpeed(float max, float min)
{
	mMaxSpeed = max;
	mMinSpeed = min;
}

void ParticleSystem::setTile(float x, float y)
{
	mMaxTileX = x;
	mMaxTileY = y;
}

void ParticleSystem::setAnimationInterval(float value)
{
	mTileInterval = value;
}

void ParticleSystem::setTileStep(float x, float y)
{
	mTileStepX = x;
	mTileStepY = y;
}

void ParticleSystem::setEmitRate(int value)
{
	mEmitRate = value;
	calculateNeedParticle();
}

void ParticleSystem::setVelocity(float x, float y, float z)
{
	mStartVelocity.x = x;
	mStartVelocity.y = y;
	mStartVelocity.z = z;
}

void ParticleSystem::play()
{
	mIsActivate = true;
}

void ParticleSystem::stop()
{
	mIsActivate = false;
}

void ParticleSystem::setDuration(float value)
{
	mDuration = value;
}

void ParticleSystem::enableLoop(bool value)
{
	mIsLoop = value;
}

const std::vector<ParticleSystem::PAttribute>& ParticleSystem::getParticles()
{
	return mParticles;
}

