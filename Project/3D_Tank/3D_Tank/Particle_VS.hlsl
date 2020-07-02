struct PointSprite
{
    float3 Pos : POSITION;
    float2 Size : SIZE;
	float4 Tile : TEXCOORD;
};

PointSprite main(PointSprite input)
{
    return input;
}