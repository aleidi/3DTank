#pragma once
#include <vector>
#include <map>
#include <DirectXMath.h>
#include "EngineCommon.h"

using namespace DirectX;

class GeometryGenerator
{
public:
	struct Vertex
	{
		XMFLOAT3 Position;
		XMFLOAT2 Texcoord;
	};

	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<UINT> indices;
	};

	enum MeshType
	{
		Cube,
		Sphere,
		Plane
	};

	static void getCube(Mesh& mesh);
	static void getSphere(Mesh& mesh);
	static void getPlane(Mesh& mesh);

private:
	static void createCube();
	static void createSphere();
	static void createPlane();
	
private:
	static std::map<MeshType, Mesh> mMeshes;
};

