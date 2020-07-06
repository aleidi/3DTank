cbuffer Transform : register(b0)
{
    matrix World;
    matrix View;
    matrix Proj;
    float2 Tile;
}

struct VS_Input
{
    float3 Pos : POSITION;
    float2 Tex : TEXCOORD;
};

struct VS_Output
{
    float4 Pos : SV_Position;
    float2 Tex : TEXCOORD;
};

VS_Output main(VS_Input input)
{
    VS_Output output;
    matrix wvp = mul(World, mul(View, Proj));
    output.Pos = mul(float4(input.Pos, 1.0f), wvp);
    output.Tex = input.Tex + Tile;
    return output;
}