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
		Cube = 0,
		Sphere = 1,
		Plane = 2,
		Panel = 3,
		Text = 4,
	};

	static void getCube(Mesh& mesh);
	static void getSphere(Mesh& mesh);
	static void getPlane(Mesh& mesh);
	static void getModel(Mesh& mesh, const std::string& name);
	static void getModel(Mesh& mesh, const std::string& name, DirectX::XMVECTOR& maxPoint, DirectX::XMVECTOR& minPoint);
	static void getUIPanel(Mesh& mesh);
	static void getUIText(Mesh& mesh) noexcept;

private:
	static void createCube();
	static void createSphere();
	static void createPlane();
	static void createModel(const std::string& name);
	static void createModel(const std::string& name, DirectX::XMVECTOR& maxPoint, DirectX::XMVECTOR& minPoint);
	static void createUIPanel();
	static void createUIText() noexcept;
	
private:
	static std::map<MeshType, Mesh> mMeshes;
	static std::map<std::string, Mesh> mModels;
};

