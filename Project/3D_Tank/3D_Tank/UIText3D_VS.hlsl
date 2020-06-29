cbuffer Transform : register(b0)
{
    matrix World;
    matrix View;
    matrix Proj;
}

struct VS_In
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct VS_Out
{
    float4 PosH : SV_Position;
	float2 Tex : TEXCOORD;
};

VS_Out main(VS_In input)
{
    VS_Out output;
    float4 posH = mul(float4(input.Pos, 1.0f), World);
    posH = mul(posH, View);
    posH = mul(posH, Proj);
    output.PosH = posH;
	output.PosH.z = 0.0f;
	output.Tex = input.Tex;
    return output;
}