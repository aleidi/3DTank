cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Proj;
}

float4 main(float3 pos : POSITION) : SV_Position
{
	return mul(mul(mul(float4(pos,1.0f),World),View),Proj);
}
