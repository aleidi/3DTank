cbuffer CBuf
{
	matrix Transform;
};

struct VS_In
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct VS_Out
{
	float4 Pos : SV_Position;
	float2 Tex : TEXCOORD;
};

VS_Out main(VS_In vin)
{
	VS_Out vout;
	vout.Pos = mul(float4(vin.Pos, 1.0f), Transform);
	vout.Tex = vin.Tex;
	return vout;
}