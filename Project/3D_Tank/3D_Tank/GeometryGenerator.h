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
		XMFLOAT3 Normal;
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
	static void getModel(Mesh& mesh, const std::string& name);
	static void getModel(Mesh& mesh, const std::string& name, DirectX::XMVECTOR& maxPoint, DirectX::XMVECTOR& minPoint);

private:
	static void createCube();
	static void createSphere();
	static void createPlane();
	static void createModel(const std::string& name);
	static void createModel(const std::string& name, DirectX::XMVECTOR& maxPoint, DirectX::XMVECTOR& minPoint);
	
private:
	static std::map<MeshType, Mesh> mMeshes;
	static std::map<std::string, Mesh> mModels;
};

