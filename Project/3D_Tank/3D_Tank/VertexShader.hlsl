cbuffer CBuf
{
    matrix transform;
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
    vout.pos = mul(float4(vin.pos, 1.0f), transform);
    return vout;
}
