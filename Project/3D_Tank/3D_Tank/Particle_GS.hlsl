struct PointSprite
{
    float3 Pos : POSITION;
    float2 Size : SIZE;
};

struct ParticleVertex
{
    float4 PosH : SV_POSITION;
    float2 Tex : TEXCOORD;
    uint PrimID : SV_PrimitiveID;
};

cbuffer ConstBuffer
{
    matrix View;
    matrix Proj;
    float3 EyePosW;
    float pad;
};

static const float4 g_Vec[2] = { float4(0.0f, 1.0f, 0.0f, 0.0f), float4(1.0f, 1.0f, 1.0f, 0.0f) };
static const float2 g_TexCoord[4] = (float2[4]) g_Vec;

[maxvertexcount(4)]
void main(point PointSprite input[1], uint primID : SV_PrimitiveID,
    inout TriangleStream<ParticleVertex> output)
{
    float3 pos = input[0].Pos;
    
    float3 up = float3(0.0f, 1.0f, 0.0f);
    float3 look = EyePosW - pos;
    look.y = 0.0f;
    look = normalize(look);
    float3 right = cross(up, look);

    float4 v[4];
    float3 center = pos;
    float halfWidth = 0.5f * input[0].Size.x;
    float halfHeight = 0.5f * input[0].Size.y;
    v[0] = float4(center + halfWidth * right - halfHeight * up, 1.0f);
    v[1] = float4(center + halfWidth * right + halfHeight * up, 1.0f);
    v[2] = float4(center - halfWidth * right - halfHeight * up, 1.0f);
    v[3] = float4(center - halfWidth * right + halfHeight * up, 1.0f);

    ParticleVertex gOut;
    matrix viewProj = mul(View, Proj);
    [unroll]
    for (int i = 0; i < 4; ++i)
    {
        gOut.PosH = mul(v[i], viewProj);
        gOut.Tex = g_TexCoord[i];
        gOut.PrimID = primID;
        output.Append(gOut);
    }

}