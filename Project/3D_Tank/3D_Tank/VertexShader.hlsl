cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Proj;
}

struct VertexInput
{
	float3 pos : POSITION;
	float4 color : COLOR;
};

struct VertexOut
{
	float4 pos : SV_Position;
	float4 color : COLOR;
};

VertexOut main(VertexInput vin)
{
    VertexOut vout;
    vout.pos = mul(float4(vin.pos, 1.0f), World);
    vout.pos = mul(vout.pos, View);
    vout.pos = mul(vout.pos, Proj);
    vout.color = vin.color;
    return vout;
}
