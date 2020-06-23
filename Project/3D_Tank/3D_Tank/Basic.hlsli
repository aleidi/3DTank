struct PointSprite
{
    float2 SizeW : SIZE;
};

struct BillboardVertex
{
    float4 PosH : SV_POSITION;
    float2 Tex : TEXCOORD;
    uint PrimID : SV_PrimitiveID;
};

Texture2D tex;
SamplerState texSamp;

cbuffer ConstBuf
{
    float4 Color;
}

cbuffer CBChangesEveryFrame
{
    matrix View;
    matrix Proj;
    float3 EyePosW;
    float Pad1;
    float3 WorldPos;
    float FillAmount;
    float2 Size;
    float2 Pad2;
}