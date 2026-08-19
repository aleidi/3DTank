#pragma once

#include <cstring>
#include <DirectXMath.h>


// 平行光源
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
	float Pad; // 構造体サイズを16の倍数に揃え、HLSLで配列を設定できるようにする
};

// 点光源
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

	// 4Dベクトルとして格納：(position, range)
	DirectX::XMFLOAT3 position;
	float range;

	// 4Dベクトルとして格納：(A0, A1, A2, Pad)
	DirectX::XMFLOAT3 Att;
	float Pad; // 構造体サイズを16の倍数に揃え、HLSLで配列を設定できるようにする
};

// スポットライト
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

	// 4Dベクトルとして格納：(position, range)
	DirectX::XMFLOAT3 position;
	float range;

	// 4Dベクトルとして格納：(Direction, Spot)
	DirectX::XMFLOAT3 Direction;
	float Spot;

	// 4Dベクトルとして格納：(Att, Pad)
	DirectX::XMFLOAT3 Att;
	float Pad; // 構造体サイズを16の倍数に揃え、HLSLで配列を設定できるようにする
};

// オブジェクトの表面材質
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
	DirectX::XMFLOAT4 Specular; // w = 鏡面反射強度
	DirectX::XMFLOAT4 Reflect;
	DirectX::XMFLOAT4 Color;
};