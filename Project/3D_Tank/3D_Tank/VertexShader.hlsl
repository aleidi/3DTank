cbuffer CBuf
{
	matrix World;
	matrix View;
	matrix Proj;
};

struct VertexInput
{
	float3 pos : POSITION;
};

struct VertexOut
{
	float4 pos : SV_Position;
};

VertexOut main(VertexInput vin)
{
    VertexOut vout;
    vout.pos = mul(float4(vin.pos, 1.0f), World);
	vout.pos = mul(vout.pos, View);
	vout.pos = mul(vout.pos, Proj);
    return vout;
}
