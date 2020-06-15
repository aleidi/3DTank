cbuffer CBuf : register(b0)
{
	matrix World;
	matrix View;
	matrix Proj;
	matrix WorldInvTranspose;
}

struct VS_Input
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
	float3 Normal : NORMAL;
};

struct VS_Out
{
	float4 PosH : SV_Position;
	float3 PosW : POSITION;
	float3 NormalW : NORMAL;
	float2 Tex : TEXCOORD;
};


VS_Out main(VS_Input vIn)
{
	VS_Out vOut;
	matrix viewProj = mul(View, Proj);
	float4 posW = mul(float4(vIn.Pos, 1.0f), World);

	vOut.PosH = mul(posW, viewProj);
	vOut.PosW = posW.xyz;
	vOut.NormalW = mul(vIn.Normal, (float3x3) WorldInvTranspose);
	vOut.Tex = vIn.Tex;
	return vOut;
}