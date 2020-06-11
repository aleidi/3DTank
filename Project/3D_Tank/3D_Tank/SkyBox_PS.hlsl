TextureCube texCube : register(t0);
SamplerState texSamp : register(s0);

struct PS_Input
{
	float4 PosH : SV_Position;
	float3 PosL : POSITION;
};

float4 main(PS_Input input) :SV_Target
{
	return texCube.Sample(texSamp, input.PosL);
}