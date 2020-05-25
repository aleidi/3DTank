struct VertexOut
{
	float4 pos : SV_Position;
	float4 color : COLOR;
};

float4 main(VertexOut pin) : SV_Target
{
    return pin.color;
}