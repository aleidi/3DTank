cbuffer Trans : register(b0)
{
	matrix mvp;
}

struct VS_Out
{
	float4 PosH : SV_Position;
	float3 PosL : POSITION;
};

VS_Out main(float3 input : POSITION)
{
	VS_Out output;
	float4 posH = mul(float4(input, 1.0f), mvp);
	output.PosH = posH.xyww;
	output.PosL = input;
	return output;
}