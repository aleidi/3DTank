cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Proj;
	matrix WorldInvTranspose;
}

struct VS_INPUT
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output;
	matrix transform = mul(World, View);
	transform = mul(transform, Proj);
	output.Pos = mul(float4(input.Pos, 1.0f), transform);
	output.Tex = input.Tex;
	return output;
}
