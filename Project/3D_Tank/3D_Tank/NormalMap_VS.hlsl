cbuffer CBuf : register(b0)
{
    matrix World;
    matrix View;
    matrix Proj;
    matrix WorldInvTranspose;
}

struct VertexPosNormalTangentTex
{
    float3 PosL : POSITION;
    float2 Tex : TEXCOORD;
    float3 NormalL : NORMAL;
    float3 TangentL : TANGENT;
};

struct VertexPosHWNormalTangentTex
{
    float4 PosH : SV_POSITION;
    float3 PosW : POSITION; // 在世界中的位置
    float3 NormalW : NORMAL; // 法向量在世界中的方向
    float4 TangentW : TANGENT; // 切线在世界中的方向
    float2 Tex : TEXCOORD;
};

// 顶点着色器
VertexPosHWNormalTangentTex main(VertexPosNormalTangentTex vIn)
{
    VertexPosHWNormalTangentTex vOut;
    
    matrix viewProj = mul(View, Proj);
    vector posW = mul(float4(vIn.PosL, 1.0f), World);

    vOut.PosW = posW.xyz;
    vOut.PosH = mul(posW, viewProj);
    vOut.NormalW = mul(vIn.NormalL, (float3x3) WorldInvTranspose);
    vOut.TangentW = mul(float4(vIn.TangentL, 0.0f), World);
    vOut.Tex = vIn.Tex;
    return vOut;
}