#include "ParticleSystem.h"
#include "Engine.h"

ParticleSystem::ParticleSystem(Graphics& gfx, const std::wstring& texture)
{
	mEmitter = Emitter::Box;

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
	};
	addBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	addBind(std::make_unique<Texture>(gfx, texture.c_str()));

	addBind(std::make_unique<Sampler>(gfx));

	addBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_POINTLIST));

	mMaterial.Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mPCBuf = std::make_unique<PixelConstantBuffer<XMFLOAT4>>(gfx, mMaterial.Color);

	CBGS cbgs;
	mGSCBuf = std::make_unique<GeometryConstantBuffer<CBGS>>(gfx, cbgs);
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
}

void ParticleSystem::updateParticle(Graphics& gfx, float deltaTime) noexcept
{
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
		}
		else
		{
			srand(Engine::sGetInstance()->getTotalTime());
			ResetParticle(&(*it));
		}
	}

}

void ParticleSystem::draw(Graphics& gfx, float deltaTime) noexcept
{
	updateParticle(gfx, deltaTime);

	SetBlendTransparent(gfx);

	mStepTime += deltaTime;
	float interval = 1.0f / mEmitRate;
	if (mParticles.size() < mNeedParticles && mParticles.size() < mMaxParticles && mStepTime > interval)
	{
		PAttribute p;
		srand(Engine::sGetInstance()->getTotalTime());
		ResetParticle(&p);
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

	mPCBuf->onUpdate(gfx, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	mVB->bind(gfx);
	mGSCBuf->bind(gfx);
	mPCBuf->bind(gfx);
	for (auto& b : mBinds)
	{
		b->bind(gfx);
	}
	gfx.DrawIndexed(4 * mParticles.size());

	ResetBlendState(gfx);
}

void ParticleSystem::ResetParticle(PAttribute* p)
{

	p->IsAlive = true;
	p->AliveTime = 0.0f;

	switch (mEmitter)
	{
	case Emitter::NoEmit:
		p->Position = mPosition;
		p->Rotation = mStartRotation;
		p->Size = mStartScale;
		p->Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
		p->Color = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.1f);
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
		XMVECTOR vel = XMVectorSet(0.0f, 1.0f * mStartSpeed, 0.0f, 0.0f);
		vel = XMVector3Rotate(vel, XMQuaternionRotationRollPitchYaw(
			XMConvertToRadians(mRotation.x), XMConvertToRadians(mRotation.y), XMConvertToRadians(mRotation.z)));
		XMStoreFloat3(&p->Velocity, vel);
		p->Color = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.1f);
		break;
	}
}

void ParticleSystem::SetBlendTransparent(Graphics& gfx)
{
	Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState;
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.AlphaToCoverageEnable = true;
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	gfx.getDevice()->CreateBlendState(&bd, pBlendState.GetAddressOf());
	gfx.getContext()->OMSetBlendState(pBlendState.Get(), nullptr, 0xFFFFFFFF);
}

void ParticleSystem::ResetBlendState(Graphics& gfx)
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

void ParticleSystem::setEmitter(Emitter type)
{
	mEmitter = type;
}

void ParticleSystem::setLifeTime(float value)
{
	mLifeTime = value;
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
}
