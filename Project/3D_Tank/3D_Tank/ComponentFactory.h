#pragma once
#include "FactoryBase.h"
#include "DirectXMath.h"

class RenderComponent;

class ComponentFactory
{
public:
	static RenderComponent* createModel(GameObject& obj, const std::string& modelPath, const std::wstring& texturePath);
	static RenderComponent* createModel(GameObject& obj, const std::string& modelPath, const std::wstring& texturePath, DirectX::XMVECTOR& maxPoint, DirectX::XMVECTOR& minPoint);

};