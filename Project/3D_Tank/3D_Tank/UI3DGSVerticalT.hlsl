#include "Basic.hlsli"

// ��ʡ�ڴ���Դ������float4����������
static const float4 g_Vec[2] = { float4(0.0f, 1.0f, 0.0f, 0.0f), float4(1.0f, 1.0f, 1.0f, 0.0f) };
static const float2 g_TexCoord[4] = (float2[4]) g_Vec;

[maxvertexcount(4)]
void main(point PointSprite input[1], uint primID : SV_PrimitiveID,
    inout TriangleStream<BillboardVertex> output)
{
    // ���㹫��������ľֲ�����ϵ�����й�����൱��
    // ��ͶӰ���˾ֲ�����ϵ��xyƽ�棬z=0
    float3 pos = WorldPos;
    
    float3 up = float3(0.0f, 1.0f, 0.0f);
    float3 look = EyePosW - pos;
    look.y = 0.0f; // look����ֻȡͶӰ��xzƽ�������
    look = normalize(look);
    float3 right = cross(up, look);

    // ������������ε��ĸ�����
    //            up
    //      v1 ___|___ v3
    //        |   |   |
    // right__|___|   |
    //        |  /    |
    //        |_/_____|
    //      v0 /       v2
    //       look  
    float4 v[4];
    float halfWidth = 0.5f * Size.x;
    float height = Size.y;
    float3 center = pos - 0.5f * height * up;
    v[0] = float4(center + halfWidth * right, 1.0f);
    v[1] = float4(center + halfWidth * right + height * up * FillAmount, 1.0f);
    v[2] = float4(center - halfWidth * right, 1.0f);
    v[3] = float4(center - halfWidth * right + height * up * FillAmount, 1.0f);

    // �Զ���λ�ý��о���任������TriangleStrip��ʽ���
    BillboardVertex gOut;
    matrix viewProj = mul(View, Proj);
    [unroll]
    for (int i = 0; i < 4; ++i)
    {

        gOut.PosH = mul(v[i], viewProj);
        gOut.Tex = g_TexCoord[i];
        gOut.PrimID = primID;
        output.Append(gOut);
    }

}