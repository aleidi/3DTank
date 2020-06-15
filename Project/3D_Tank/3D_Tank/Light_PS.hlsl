#include "LightHelper.hlsli"

Texture2D tex : register(t0);
SamplerState texSamp : register(s0);

cbuffer CBUF : register(b0)
{
	Material Mat;
	DirectionalLight DirLight;
	float3 EyePosW;
	float Pad;
}

struct PS_Input
{
	float4 PosH : SV_Position;
	float3 PosW : POSITION;
	float3 NormalW : NORMAL;
	float2 Tex : TEXCOORD;
};

float4 main(PS_Input pIn) : SV_Target
{
	float4 result = tex.Sample(texSamp, pIn.Tex);

	pIn.NormalW = normalize(pIn.NormalW);

	float3 toEyeW = normalize(EyePosW - pIn.PosW);

	float4 ambient, diffuse, spec;
	float4 A, D, S;
	ambient = diffuse = spec = A = D = S = float4(0.0f, 0.0f, 0.0f, 0.0f);

	ComputeDirectionalLight(Mat, DirLight, pIn.NormalW, toEyeW, A, D, S);
	ambient += A;
	diffuse += D;
	spec += S;

	float4 litColor = ((ambient + diffuse) + spec) * result;

	litColor.a = Mat.Diffuse.a * Mat.Color.a;

	return litColor;
}