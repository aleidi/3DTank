Texture2D tex : register(t0);
SamplerState texSamp : register(s0);

struct PS_In
{
	float4 Pos : SV_Position;
	float2 Tex : TEXCOORD;
};

float4 main(PS_In pin) : SV_Target
{
	return tex.Sample(texSamp, pin.Tex);
}