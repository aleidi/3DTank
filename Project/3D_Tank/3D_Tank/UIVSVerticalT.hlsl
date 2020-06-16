cbuffer CBuf
{
	matrix Transform;
	float FillAmount;
	float3 pad;
};

struct VS_In
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct VS_Out
{
	float4 Pos : SV_Position;
	float2 Tex : TEXCOORD;
};

VS_Out main(VS_In vin)
{
	VS_Out vout;
	float3 pos;
	float2 tex;
	float fill;

	fill = clamp(FillAmount, 0.0f, 1.0f);

	[flatten]
	if (vin.Pos.y > 0.5f)
	{
		pos.x = vin.Pos.x;
		pos.y = fill;
		tex.x = vin.Tex.x;
		tex.y = fill;
	}
	else
	{
		pos = vin.Pos;
		tex = vin.Tex;
	}

	vout.Pos = mul(float4(pos, 1.0f), Transform);
	vout.Tex = tex;
	return vout;
}