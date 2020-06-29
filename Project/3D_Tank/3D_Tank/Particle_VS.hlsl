struct PointSprite
{
    float3 Pos : POSITION;
    float2 Size : SIZE;
};

PointSprite main(PointSprite input)
{
    return input;
}