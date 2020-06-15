#pragma once

#include <cstring>
#include <DirectXMath.h>


// 方向光
struct DirectionalLight
{
	DirectionalLight() = default;

	DirectionalLight(const DirectionalLight&) = default;
	DirectionalLight& operator=(const DirectionalLight&) = default;

	DirectionalLight(DirectionalLight&&) = default;
	DirectionalLight& operator=(DirectionalLight&&) = default;

	DirectionalLight(const DirectX::XMFLOAT4& _Ambient, const DirectX::XMFLOAT4& _Diffuse, const DirectX::XMFLOAT4& _Specular,
		const DirectX::XMFLOAT3& _Direction) :
		Ambient(_Ambient), Diffuse(_Diffuse), Specular(_Specular), Direction(_Direction), Pad() {}

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;
	DirectX::XMFLOAT3 Direction;
	float Pad; // 最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};

// 点光
struct PointLight
{
	PointLight() = default;

	PointLight(const PointLight&) = default;
	PointLight& operator=(const PointLight&) = default;

	PointLight(PointLight&&) = default;
	PointLight& operator=(PointLight&&) = default;

	PointLight(const DirectX::XMFLOAT4& _Ambient, const DirectX::XMFLOAT4& _Diffuse, const DirectX::XMFLOAT4& _Specular,
		const DirectX::XMFLOAT3& _position, float _range, const DirectX::XMFLOAT3& _Att) :
		Ambient(_Ambient), Diffuse(_Diffuse), Specular(_Specular), position(_position), range(_range), Att(_Att), Pad() {}

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;

	// 打包成4D向量: (position, range)
	DirectX::XMFLOAT3 position;
	float range;

	// 打包成4D向量: (A0, A1, A2, Pad)
	DirectX::XMFLOAT3 Att;
	float Pad; // 最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};

// 聚光灯
struct SpotLight
{
	SpotLight() = default;

	SpotLight(const SpotLight&) = default;
	SpotLight& operator=(const SpotLight&) = default;

	SpotLight(SpotLight&&) = default;
	SpotLight& operator=(SpotLight&&) = default;

	SpotLight(const DirectX::XMFLOAT4& _Ambient, const DirectX::XMFLOAT4& _Diffuse, const DirectX::XMFLOAT4& _Specular,
		const DirectX::XMFLOAT3& _position, float _range, const DirectX::XMFLOAT3& _Direction,
		float _Spot, const DirectX::XMFLOAT3& _Att) :
		Ambient(_Ambient), Diffuse(_Diffuse), Specular(_Specular),
		position(_position), range(_range), Direction(_Direction), Spot(_Spot), Att(_Att), Pad() {}

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;

	// 打包成4D向量: (position, range)
	DirectX::XMFLOAT3 position;
	float range;

	// 打包成4D向量: (Direction, Spot)
	DirectX::XMFLOAT3 Direction;
	float Spot;

	// 打包成4D向量: (Att, Pad)
	DirectX::XMFLOAT3 Att;
	float Pad; // 最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};

// 物体表面材质
struct Material
{
	Material() = default;

	Material(const Material&) = default;
	Material& operator=(const Material&) = default;

	Material(Material&&) = default;
	Material& operator=(Material&&) = default;

	Material(const DirectX::XMFLOAT4& _Ambient, const DirectX::XMFLOAT4& _Diffuse, const DirectX::XMFLOAT4& _Specular,
		const DirectX::XMFLOAT4& _Reflect) :
		Ambient(_Ambient), Diffuse(_Diffuse), Specular(_Specular), Reflect(_Reflect) {}

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular; // w = 镜面反射强度
	DirectX::XMFLOAT4 Reflect;
	DirectX::XMFLOAT4 Color;
};