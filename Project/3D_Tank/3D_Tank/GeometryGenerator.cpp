#include "GeometryGenerator.h"

std::map<EngineRender::MeshType, GeometryGenerator::Mesh> GeometryGenerator::mMeshes;

void GeometryGenerator::getMesh(EngineRender::MeshType type, Mesh& mesh)
{
	if (mMeshes[type].vertices.size() == 0 || mMeshes[type].indices.size() == 0)
	{
		switch (type)
		{
		case EngineRender::MeshType::BOX:
			createBox();
			break;
		case EngineRender::MeshType::Sphere:
			createSphere();
			break;
		case EngineRender::MeshType::Plane:
			createPlane();
			break;
		}
	}

	mesh = mMeshes[type];
}

void GeometryGenerator::createBox()
{
	const std::vector<Vertex> vertices =
	{
		{ -1.0f,-1.0f,-1.0f },
		{ 1.0f,-1.0f,-1.0f },
		{ -1.0f,1.0f,-1.0f },
		{ 1.0f,1.0f,-1.0f },
		{ -1.0f,-1.0f,1.0f },
		{ 1.0f,-1.0f,1.0f },
		{ -1.0f,1.0f,1.0f },
		{ 1.0f,1.0f,1.0f },
	};

	const std::vector<UINT> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	mMeshes[EngineRender::MeshType::BOX].vertices = vertices;
	mMeshes[EngineRender::MeshType::BOX].indices = indices;
}

void GeometryGenerator::createSphere()
{
}

void GeometryGenerator::createPlane()
{
}