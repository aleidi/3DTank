#pragma once
#include "FactoryBase.h"
#include "DirectXMath.h"

class ComponentFactory
{
public:
	static void createModel(GameObject& obj, const std::string& modelPath, const std::wstring& texturePath);
	static void createModel(GameObject& obj, const std::string& modelPath, const std::wstring& texturePath, DirectX::XMVECTOR& maxPoint, DirectX::XMVECTOR& minPoint);

};

