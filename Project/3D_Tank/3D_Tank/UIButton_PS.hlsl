Texture2D tex : register(t0);
SamplerState texSamp : register(s0);

cbuffer ConstBuf : register(b0)
{
	float4 Color;
}

struct PS_In
{
	float4 Pos : SV_Position;
	float2 Tex : TEXCOORD;
};

float4 main(PS_In pin) : SV_Target
{
	return tex.Sample(texSamp, pin.Tex) * Color;
}