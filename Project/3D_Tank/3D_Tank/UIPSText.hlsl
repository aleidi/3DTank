Texture2D tex : register(t0);
SamplerState texSamp : register(s0);

struct PS_Input
{
	float4 Pos : SV_Position;
	float2 Tex : TEXCOORD;
};

float4 main(PS_Input input) :SV_Target
{
	return float4(tex.Sample(texSamp, input.Tex).rrr, 1.0f);
}