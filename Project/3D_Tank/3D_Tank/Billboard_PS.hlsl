#include "Basic.hlsli"

float4 main(BillboardVertex pin) : SV_Target
{
    return tex.Sample(texSamp, pin.Tex) * Color;
   // return float4(1.0, 1.0f, 1.0f, 1.0f);
}