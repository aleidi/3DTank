#include "LightHelper.hlsli"

struct VertexPosHWNormalTangentTex
{
    float4 PosH : SV_POSITION;
    float3 PosW : POSITION;
    float3 NormalW : NORMAL; 
    float4 TangentW : TANGENT;
    float2 Tex : TEXCOORD;
};

Texture2D tex : register(t0);
Texture2D NormalMap : register(t1);
SamplerState texSamp : register(s0);

cbuffer CBUF : register(b0)
{
    Material Mat;
    DirectionalLight DirLight;
    float3 EyePosW;
    float Fresnel;
}

float4 main(VertexPosHWNormalTangentTex pIn) : SV_Target
{
    float4 result = tex.Sample(texSamp, pIn.Tex);
    
    pIn.NormalW = normalize(pIn.NormalW);

    float3 toEyeW = normalize(EyePosW - pIn.PosW);
    
    float3 normalMapSample = NormalMap.Sample(texSamp, pIn.Tex).rgb;
    float3 bumpedNormalW = NormalSampleToWorldSpace(normalMapSample, pIn.NormalW, pIn.TangentW);

    float4 ambient, diffuse, spec;
    float4 A, D, S;
    float F;
    ambient = diffuse = spec = A = D = S = float4(0.0f, 0.0f, 0.0f, 0.0f);
    
    ComputeDirectionalLight(Mat, DirLight, bumpedNormalW, toEyeW, Fresnel, A, D, S, F);
    ambient += A;
    diffuse += D;
    spec += S;

    float4 litColor = (ambient + diffuse + spec * F) * result;
	
    litColor.a = Mat.Diffuse.a * Mat.Color.a;
	
    return litColor;
}
