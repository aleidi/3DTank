Texture2D txDiffuse1 : register(t0);
Texture2D txDiffuse2 : register(t1);
SamplerState texSampler : register(s0);

cbuffer ConstBuffer
{
    float4 Color;
};

struct PS_Input
{
    float4 Pos : SV_Position;
    float2 Tex : TEXCOORD0;
};

float4 main(PS_Input input) : SV_Target
{
    float4 res1 = txDiffuse1.Sample(texSampler, input.Tex);
    float4 res2 = txDiffuse2.Sample(texSampler, input.Tex);
    return (res1 + res2) * Color;

}