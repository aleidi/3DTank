#pragma once
#include <vector>
#include <DirectXMath.h>
#include "EnginePlat.h"

using namespace DirectX;

class GeometryGenerator
{
public:
	struct Vertex
	{
		Vertex(){}
		Vertex(float px,float py, float pz)
			:Position(px,py,pz)
		{}
		XMFLOAT3 Position;
	};

	void CreateBox(std::vector<Vertex>& vertices, std::vector<UINT>& indices);
	void CreateSphere(std::vector<Vertex>& vertices, std::vector<UINT>& indices);
	void CreatePlane(std::vector<Vertex>& vertices, std::vector<UINT>& indices);
};

