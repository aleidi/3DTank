struct ParticleVertex
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

float4 main(ParticleVertex pin) : SV_Target
{
    return tex.Sample(texSamp, pin.Tex) * Color;
}