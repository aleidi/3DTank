#pragma once
#include "FactoryBase.h"

class ComponentFactory
{
public:
	static void createModel(GameObject& obj, const std::string& modelPath, const std::wstring& texturePath);

};

