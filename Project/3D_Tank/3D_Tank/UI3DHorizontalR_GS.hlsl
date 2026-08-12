#include "Basic.hlsli"

static const float4 g_Vec[2] = { float4(0.0f, 1.0f, 0.0f, 0.0f), float4(1.0f, 1.0f, 1.0f, 0.0f) };
static const float2 g_TexCoord[4] = (float2[4]) g_Vec;

[maxvertexcount(4)]
void main(point PointSprite input[1], uint primID : SV_PrimitiveID,
    inout TriangleStream<BillboardVertex> output)
{
    float3 pos = WorldPos;
    
    float3 up = float3(0.0f, 1.0f, 0.0f);
    float3 look = EyePosW - pos;
    look.y = 0.0f;
    look = normalize(look);
    float3 right = cross(up, look);

    float4 v[4];
    float width = Size.x;
    float halfHeight = 0.5f * Size.y;
    float3 center = pos + 0.5f * width * right;
    v[0] = float4(center - halfHeight * up, 1.0f);
    v[1] = float4(center + halfHeight * up, 1.0f);
    v[2] = float4(center - width * right * FillAmount - halfHeight * up, 1.0f);
    v[3] = float4(center - width * right * FillAmount + halfHeight * up, 1.0f);

    BillboardVertex gOut;
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