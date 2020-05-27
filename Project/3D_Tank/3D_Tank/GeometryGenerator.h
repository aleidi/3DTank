#pragma once
#include <vector>
#include <map>
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

	struct Model
	{
		std::vector<Vertex> vertices;
		std::vector<UINT> indices;
	};

	enum MeshType
	{
		BOX,
		Sphere,
		Plane
	};

	static void getModel(MeshType type, Model& mesh);

private:



	static void createBox();
	static void createSphere();
	static void createPlane();
	
private:
	static std::map<MeshType,Model> mMeshes;
};

